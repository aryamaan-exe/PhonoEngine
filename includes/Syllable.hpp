#ifndef SYLLABLE_HPP
#define SYLLABLE_HPP

#include <vector>

#include "Phoneme.hpp"

class Syllable {
public:
  Syllable(std::vector<Phoneme>& onset,
           std::vector<Phoneme>& nucleus,
           std::vector<Phoneme>& coda);

private:
  std::vector<Phoneme> onset_;
  std::vector<Phoneme> nucleus_;
  std::vector<Phoneme> coda_;
};

#endif