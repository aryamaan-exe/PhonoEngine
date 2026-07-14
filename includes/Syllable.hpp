#ifndef SYLLABLE_HPP
#define SYLLABLE_HPP

#include <vector>

#include "Phoneme.hpp"

using SyllablePart = std::vector<Phoneme*>;

class Syllable {
public:
  Syllable(const SyllablePart& onset,
           const SyllablePart& nucleus,
           const SyllablePart& coda);

  SyllablePart GetOnset() const;
  SyllablePart GetNucleus() const;
  SyllablePart GetCoda() const;

  std::wstring Symbols() const;

private:
  SyllablePart onset_;
  SyllablePart nucleus_;
  SyllablePart coda_;
};

#endif