#include "Language.hpp"

#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>

#include "Rule.hpp"
#include "Syllable.hpp"

using json = nlohmann::json;

std::wstring Language::Utf8ToWide(const std::string& utf8) {
  std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  return converter.from_bytes(utf8);
}

Language::Language(const std::string& filename) {
  std::ifstream ifs{filename};
  json language_data = json::parse(ifs);

  for (const auto& symbol :
       language_data["ipa"].get<std::vector<std::string>>()) {
    AddIPAPhoneme(Utf8ToWide(symbol));
  }

  // for (const auto& phoneme_data : language_data["phonemes"]) {
  //   Symbol symbol{phoneme_data["symbol"]};
  //   auto type{phoneme_data["type"]};

  //   if (type == "consonant") {
  //     Place place{phoneme_data["place"]};
  //     Manner manner{phoneme_data["manner"]};
  //     bool voiced{phoneme_data["voiced"]};

  //     AddPhoneme(std::make_unique<Consonant>(symbol, place, manner, voiced));
  //   } else if (type == "vowel") {
  //     Height height{phoneme_data["height"]};
  //     Backness backness{phoneme_data["backness"]};
  //     bool tense{phoneme_data["tense"]};
  //     bool rounded{phoneme_data["rounded"]};

  //     AddPhoneme(
  //         std::make_unique<Vowel>(symbol, height, backness, tense, rounded));
  //   } else {
  //     throw std::invalid_argument("Phoneme type must be consonant or
  //     vowel.");
  //   }
  // };
}

void Language::AddPhoneme(std::unique_ptr<Phoneme> phoneme) {
  Symbol symbol = phoneme->GetSymbol();
  symbols_.insert({symbol, std::move(phoneme)});
}

void Language::AddIPAPhoneme(const Symbol& ipa_symbol) {
  auto* prototype{kIPAChart.at(ipa_symbol).get()};
  AddPhoneme(prototype->Clone());
}

void Language::AddRule(const Rule& rule) {
  rules_.push_back(std::make_unique<Rule>(rule));
}

void Language::AddSyllabicConsonant(const Symbol& symbol) {
  syllabic_consonants_.insert(symbol);
}

void Language::AddDiphthong(const Symbol& first, const Symbol& second) {
  diphthongs_.insert({first, second});
}

bool Language::IsNucleusCapable(const Phoneme* phoneme) const {
  return phoneme->GetType() == PhonemeType::kVowel ||
         syllabic_consonants_.contains(phoneme->GetSymbol());
}

bool Language::FormsDiphthongWith(const Symbol& prev,
                                  const Symbol& next) const {
  return diphthongs_.contains({prev, next});
}

void Language::SetTokenConverter(TokenConverter converter) {
  converter_ = std::move(converter);
}

ValidationResult Language::Validate(const Word& word) const {
  std::vector<Syllable> syllables = word.GetSyllables();

  for (const Syllable& syllable : syllables) {
    SyllablePart onset = syllable.GetOnset();
    SyllablePart nucleus = syllable.GetNucleus();
    SyllablePart coda = syllable.GetCoda();

    for (auto& rule : rules_) {
      const auto& segment =
          [&rule, &onset, &nucleus, &coda]() -> const SyllablePart& {
        switch (rule->GetType()) {
        case RuleType::Onset:
          return onset;
        case RuleType::Nucleus:
          return nucleus;
        case RuleType::Coda:
          return coda;
        }
        throw std::logic_error("Invalid rule type");
      }();

      if (!rule->IsValid(segment)) {
        return {false, rule->GetName()};
      }
    }
  }

  return {true, L""};
}

Phoneme* Language::GetPhonemeFromSymbol(const Symbol& symbol) const {
  auto it = symbols_.find(symbol);
  if (it == symbols_.end()) {
    throw std::runtime_error("Symbol not found in phonemic inventory");
  }
  return it->second.get();
}

Word Language::BuildWordFromSymbols(std::vector<Symbol>& word) {
  std::vector<Syllable> syllables;
  SyllablePart onset;
  SyllablePart nucleus;
  SyllablePart coda;
  SyllablePart* curr{&onset};
  short it = -1;
  for (const auto& c : word) {
    if (c == L".") {
      ++it;
      it %= 3;
      switch (it) {
      case 0:
        curr = &onset;
        break;
      case 1:
        curr = &nucleus;
        break;
      case 2:
        curr = &coda;
        syllables.emplace_back(onset, nucleus, coda);
        onset.clear();
        nucleus.clear();
        coda.clear();
        break;
      }
    } else {
      if (!symbols_.contains(c)) {
        throw std::format(
            L"The symbol '{}' was not found in phonemic inventory.", c);
      }

      auto* phoneme = symbols_.at(c).get();
      curr->push_back(phoneme);
    }
  }
  Word result{syllables};
  return result;
}

std::vector<Syllable> Language::GetSyllablesFromTokens(
    const std::vector<std::wstring>& tokens) const {
  std::vector<Syllable> result;

  SyllablePart onset, nucleus, coda;
  bool has_nucleus{};

  for (size_t i{1}; i < tokens.size(); ++i) {
    const std::wstring& tok{tokens.at(i)};
    if (tok == L"#") break;

    auto converted{converter_(tok)};
    if (converted == std::nullopt) {
      throw std::logic_error("Invalid token passed for parsing.");
    };

    auto* phoneme = GetPhonemeFromSymbol(converted.value());

    if (IsNucleusCapable(phoneme)) {
      if (!has_nucleus) {
        nucleus.push_back(phoneme);
        has_nucleus = true;
      } else if (FormsDiphthongWith(nucleus.back()->GetSymbol(),
                                    phoneme->GetSymbol())) {
        nucleus.push_back(phoneme);
      } else {
        SyllablePart next_onset = coda;
        result.emplace_back(onset, nucleus, SyllablePart{});
        onset = std::move(next_onset);
        nucleus.clear();
        coda.clear();
        nucleus.push_back(phoneme);
      }
    } else {
      (has_nucleus ? coda : onset).push_back(phoneme);
    }
  }

  if (has_nucleus || !onset.empty()) {
    result.emplace_back(onset, nucleus, coda);
  }

  return result;
}

std::wostream& operator<<(std::wostream& os, Language& language) {
  os << "SYMBOLS:\n";
  for (const auto& [symbol, _] : language.symbols_) {
    os << symbol << ' ';
  }

  os << "\nRULES:\n";
  for (const auto& rule : language.rules_) {
    os << rule->GetName() << '\n';
  }

  os.flush();

  return os;
}