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

  Symbol Symbols() const;

  static std::vector<Syllable> GetSyllablesFromTokens(const std::vector<std::string>& tokens);

private:
  SyllablePart onset_;
  SyllablePart nucleus_;
  SyllablePart coda_;
};

#endif