#include "Syllable.hpp"

Syllable::Syllable(const SyllablePart& onset,
                   const SyllablePart& nucleus,
                   const SyllablePart& coda):
    onset_(onset), nucleus_(nucleus), coda_(coda) {}

SyllablePart Syllable::GetOnset() const { return onset_; }

SyllablePart Syllable::GetNucleus() const { return nucleus_; }

SyllablePart Syllable::GetCoda() const { return coda_; }

Symbol Syllable::Symbols() const {
  std::wstring res;
  for (Phoneme* p : onset_) {
    res += p->GetSymbol();
  }
  for (Phoneme* p : nucleus_) {
    res += p->GetSymbol();
  }
  for (Phoneme* p : coda_) {
    res += p->GetSymbol();
  }

  return res;
}

std::vector<Syllable> Syllable::GetSyllablesFromTokens([[maybe_unused]] const std::vector<std::string>& tokens) {
  std::vector<Syllable> result;

  return result;
}
