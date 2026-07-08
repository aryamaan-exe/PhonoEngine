#include "Word.hpp"

Word::Word(const std::vector<Syllable>& syllables): syllables_(syllables) {}

std::wstring Word::Symbols() {
  std::wstring res;
  for (const Syllable& s : syllables_) {
    res += s.Symbols();
  }

  return res;
}

std::vector<Syllable> Word::GetSyllables() { return syllables_; }