#ifndef WORD_HPP
#define WORD_HPP

#include "Syllable.hpp"

class Word {
public:
  Word(const std::vector<Syllable>& syllables);
  Word(const std::string& spelling, const std::vector<Syllable>& syllables);
  std::string GetSpelling();
  std::vector<Syllable> GetSyllables();
  std::wstring Symbols() const;

private:
  std::string spelling_;
  std::vector<Syllable> syllables_;
};

#endif