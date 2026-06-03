#include <iostream>
#include <vector>
#include "Consonant.hpp"
#include "Syllable.hpp"
#include "Vowel.hpp"

int main() {
  auto b = new Consonant("b", Place::Bilabial, Manner::Plosive, true);
  auto a = new Vowel("a", Height::Low, Backness::Front, true, false);
  auto r = new Consonant("ɹ", Place::Alveolar, Manner::Approximant, true);
  std::vector<Phoneme*> o{b};
  std::vector<Phoneme*> n{a};
  std::vector<Phoneme*> c{r};

  auto *bar = new Syllable(o, n, c);
  std::cout << bar->Symbols() << std::endl;
}
