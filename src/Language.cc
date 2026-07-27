#include "Language.hpp"

#include <format>
#include <memory>
#include <stdexcept>

#include "Rule.hpp"
#include "Syllable.hpp"

void Language::AddPhoneme(std::unique_ptr<Phoneme> phoneme) {
  Symbol symbol = phoneme->GetSymbol();
  Phoneme* raw = phoneme.get();
  inventory_.push_back(std::move(phoneme));
  symbols_.insert({symbol, raw});
}

void Language::AddRule(Rule* rule) { rules_.push_back(rule); }

bool Language::Validate(Word word) {
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
        throw std::format(L"{} is invalid: {}", word.Symbols(), rule->GetName());
      }
    }
  }

  return true;
}

Phoneme* Language::GetPhonemeFromSymbol(Symbol symbol) {
  auto it = symbols_.find(symbol);
  if (it == symbols_.end()) {
    throw std::runtime_error("Symbol not found in phonemic inventory");
  }
  return it->second;
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

      auto* phoneme = symbols_.at(c);
      curr->push_back(phoneme);
    }
  }
  Word result{syllables};
  return result;
}

std::vector<Syllable> Language::GetSyllablesFromTokens(const std::vector<std::wstring>& tokens) {
  std::vector<Syllable> result;

  SyllablePart onset, nucleus, coda;
  SyllablePart* syllable_part{&onset};
  RuleType current_part{RuleType::Onset};

  for (size_t i{1}; i < tokens.size(); ++i) {
    std::wstring tok{tokens.at(i)};
    if (tok == L"#") break;

    auto* p{GetPhonemeFromSymbol(tok)};
    syllable_part->push_back(p);
    
    for (auto& rule : rules_) {
      if (rule->GetType() != current_part) continue;

      if (!rule->IsValid(*syllable_part) && syllable_part->empty()) {
        syllable_part->pop_back();
        
        switch (current_part) {
          case RuleType::Onset:
            current_part = RuleType::Nucleus;
            syllable_part = &nucleus;
            break;
          case RuleType::Nucleus:
            current_part = RuleType::Coda;
            syllable_part = &coda;
            break;
          case RuleType::Coda:
            current_part = RuleType::Onset;
            syllable_part = &onset;
            result.emplace_back(onset, nucleus, coda);
            onset.clear();
            nucleus.clear();
            coda.clear();
            break;
          default:
            throw std::logic_error("Unknown rule type reached.");
            break;
        }
      }
    }
  }

  return result;
}
