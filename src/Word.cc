#include "Word.hpp"

Word::Word(const std::vector<Syllable>& syllables): syllables_(syllables) {}

std::string Word::Symbols() {
  std::string res;
  for (Syllable s : syllables_) {
    res += s.Symbols();
  }

  return res;
}

std::vector<Syllable> Word::GetSyllables() { return syllables_; }