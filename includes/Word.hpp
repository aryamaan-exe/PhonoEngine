#ifndef WORD_HPP
#define WORD_HPP

#include "Syllable.hpp"

class Word {
public:
  Word(const std::vector<Syllable>& syllables);
  std::vector<Syllable> GetSyllables();
  std::string Symbols();

private:
  std::vector<Syllable> syllables_;
};

#endif