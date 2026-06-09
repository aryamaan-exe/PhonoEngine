#include "Language.hpp"

#include <stdexcept>

#include "Rule.hpp"
#include "Syllable.hpp"

void Language::AddPhoneme(Phoneme* phoneme) { inventory_.push_back(*phoneme); }

void Language::AddRule(const Rule* rule) { rules_.push_back(*rule); }

bool Language::Validate(Word word) {
  std::vector<Syllable> syllables = word.GetSyllables();

  for (const Syllable& syllable : syllables) {
    std::vector<Phoneme*> onset = syllable.GetOnset();
    std::vector<Phoneme*> nucleus = syllable.GetNucleus();
    std::vector<Phoneme*> coda = syllable.GetCoda();

    for (Rule& rule : rules_) {
      switch (rule.GetType()) {
      case (RuleType::Onset):
        if (!rule.IsValid(onset)) throw std::runtime_error(rule.GetName());
        break;
      case (RuleType::Nucleus):
        if (!rule.IsValid(nucleus)) throw std::runtime_error(rule.GetName());
        break;
      case (RuleType::Coda):
        if (!rule.IsValid(coda)) throw std::runtime_error(rule.GetName());
        break;
      }
    }
  }

  return true;
}