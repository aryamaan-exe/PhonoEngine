#ifndef SYLLABLE_HPP
#define SYLLABLE_HPP

#include <vector>

#include "Phoneme.hpp"

class Syllable {
public:
  Syllable(const std::vector<Phoneme*>& onset,
           const std::vector<Phoneme*>& nucleus,
           const std::vector<Phoneme*>& coda);

  std::vector<Phoneme*> GetOnset() const;
  std::vector<Phoneme*> GetNucleus() const;
  std::vector<Phoneme*> GetCoda() const;

  std::string Symbols() const;

private:
  std::vector<Phoneme*> onset_;
  std::vector<Phoneme*> nucleus_;
  std::vector<Phoneme*> coda_;
};

#endif