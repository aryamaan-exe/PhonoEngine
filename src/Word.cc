#include "Word.hpp"

Word::Word(const std::vector<Syllable>& syllables): syllables_(syllables) {}

Word::Word(const std::string& spelling, const std::vector<Syllable>& syllables):
    spelling_(spelling), syllables_(syllables) {}

std::wstring Word::Symbols() const {
  std::wstring res;
  for (const Syllable& s : syllables_) {
    res += s.Symbols();
  }

  return res;
}

std::string Word::GetSpelling() { return spelling_; }

std::vector<Syllable> Word::GetSyllables() { return syllables_; }