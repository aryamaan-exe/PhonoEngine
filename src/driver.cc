#include <iostream>

#include "Consonant.hpp"
#include "Vowel.hpp"
#include "Syllable.hpp"

int main() {
  Consonant c("b", Place::Bilabial, Manner::Plosive, true);
  Vowel v("a", Height::Low, Backness::Front, true, false); 
  Consonant c2("ɹ", Place::Alveolar, Manner::Approximant, true);

  Syllable s;
}
