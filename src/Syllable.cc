#include "Syllable.hpp"

Syllable::Syllable(const SyllablePart& onset,
                   const SyllablePart& nucleus,
                   const SyllablePart& coda):
    onset_(std::move(onset)), nucleus_(std::move(nucleus)), coda_(std::move(coda)) {}

SyllablePart Syllable::GetOnset() const { return onset_; }

SyllablePart Syllable::GetNucleus() const { return nucleus_; }

SyllablePart Syllable::GetCoda() const { return coda_; }

Symbol Syllable::Symbols() const {
  std::wstring res;
  for (const auto& p : onset_) {
    res += p->GetSymbol();
  }
  for (const auto& p : nucleus_) {
    res += p->GetSymbol();
  }
  for (const auto& p : coda_) {
    res += p->GetSymbol();
  }

  return res;
}

