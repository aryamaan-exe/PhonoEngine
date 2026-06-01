#include "Syllable.hpp"

Syllable::Syllable(std::vector<Phoneme>& onset,
                   std::vector<Phoneme>& nucleus,
                   std::vector<Phoneme>& coda):
    onset_(onset), nucleus_(nucleus), coda_(coda) {}