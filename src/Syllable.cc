#include "Syllable.hpp"

Syllable::Syllable(const std::vector<Phoneme*>& onset,
                   const std::vector<Phoneme*>& nucleus,
                   const std::vector<Phoneme*>& coda):
    onset_(onset), nucleus_(nucleus), coda_(coda) {}

std::vector<Phoneme*> Syllable::GetOnset() const { return onset_; }

std::vector<Phoneme*> Syllable::GetNucleus() const { return nucleus_; }

std::vector<Phoneme*> Syllable::GetCoda() const { return coda_; }

std::wstring Syllable::Symbols() const {
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
