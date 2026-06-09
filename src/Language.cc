#include "Language.hpp"

#include "Syllable.hpp"

void Language::AddPhoneme(Phoneme* phoneme) { inventory_.push_back(*phoneme); }

void Language::AddRule(const Rule* rule) { rules_.push_back(*rule); }

bool Language::Validate(Word word) {
  std::vector<Syllable> syllables = word.GetSyllables();

  // TODO: Check if rule type (onset rule, nucleus rule, coda rule) matches syllable part type
}