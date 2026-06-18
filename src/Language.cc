#include "Language.hpp"

#include <format>
#include <memory>
#include <stdexcept>

#include "Rule.hpp"
#include "Syllable.hpp"

void Language::AddPhoneme(Phoneme* phoneme) {
  inventory_.push_back(*phoneme);
  symbols_.insert({phoneme->GetSymbol(), *phoneme});
}

void Language::AddRule(const Rule* rule) { rules_.push_back(*rule); }

bool Language::Validate(Word word) {
  std::vector<Syllable> syllables = word.GetSyllables();

  for (const Syllable& syllable : syllables) {
    std::vector<Phoneme*> onset = syllable.GetOnset();
    std::vector<Phoneme*> nucleus = syllable.GetNucleus();
    std::vector<Phoneme*> coda = syllable.GetCoda();

    for (Rule& rule : rules_) {
      const auto& segment =
          [&rule, &onset, &nucleus, &coda]() -> const std::vector<Phoneme*>& {
        switch (rule.GetType()) {
        case RuleType::Onset:
          return onset;
        case RuleType::Nucleus:
          return nucleus;
        case RuleType::Coda:
          return coda;
        }
        throw std::logic_error("Invalid rule type");
      }();

      if (!rule.IsValid(segment)) {
        throw std::runtime_error(
            std::format("{} is invalid: {}", word.Symbols(), rule.GetName()));
      }
    }
  }

  return true;
}

Phoneme Language::GetPhonemeFromSymbol(std::string& symbol) {
  if (!symbols_.contains(symbol)) {
    throw std::invalid_argument(std::format(
        "The symbol '{}' was not found in phonemic inventory.", symbol));
  }

  return symbols_.at(symbol);
}

Word Language::BuildWordFromSymbols(std::vector<std::string>& word) {
  std::vector<Syllable> syllables;
  std::vector<Phoneme*> onset;
  std::vector<Phoneme*> nucleus;
  std::vector<Phoneme*> coda;
  std::vector<Phoneme*>* curr{&onset};
  short it = -1;
  for (const auto& c : word) {
    if (c == ".") {
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
        throw std::invalid_argument(std::format(
            "The symbol '{}' was not found in phonemic inventory.", c));
      }

      curr->push_back(&symbols_.at(c));
    }
  }
  Word result{syllables};
  return result;
}