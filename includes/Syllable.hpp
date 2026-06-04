#ifndef SYLLABLE_HPP
#define SYLLABLE_HPP

#include <vector>

#include "Phoneme.hpp"

class Syllable {
public:
  Syllable(const std::vector<Phoneme*>& onset,
           const std::vector<Phoneme*>& nucleus,
           const std::vector<Phoneme*>& coda);

  std::vector<Phoneme*> GetOnset();
  std::vector<Phoneme*> GetNucleus();
  std::vector<Phoneme*> GetCoda();

  std::string Symbols();

private:
  std::vector<Phoneme*> onset_;
  std::vector<Phoneme*> nucleus_;
  std::vector<Phoneme*> coda_;
};

#endif