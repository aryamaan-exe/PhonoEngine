#include <iostream>
#include <vector>

#include "Consonant.hpp"
#include "Rule.hpp"
#include "Syllable.hpp"
#include "Vowel.hpp"
#include "Word.hpp"

int main() {
  auto* b = new Consonant("b", Place::Bilabial, Manner::Plosive, true);
  auto* a = new Vowel("a", Height::Low, Backness::Front, true, false);
  auto* r = new Consonant("ɹ", Place::Alveolar, Manner::Approximant, true);

  std::vector<Phoneme*> o{b};
  std::vector<Phoneme*> n{a};
  std::vector<Phoneme*> c{r};
  std::vector<Phoneme*> e;

  auto* bar = new Syllable(o, n, c);
  auto* rb = new Syllable(c, e, o);
  std::cout << bar->Symbols() << std::endl;

  auto* rule = new Rule(
      "Nucleus must exist",
      [](const std::vector<Phoneme*>& nucleus) { return !nucleus.empty(); });

  std::cout << std::boolalpha << rule->IsValid(bar->GetNucleus()) << std::endl;
  std::cout << std::boolalpha << rule->IsValid(rb->GetNucleus()) << std::endl;

  auto* code = new Syllable(
      {new Consonant("k", Place::Velar, Manner::Plosive, false)},
      {new Vowel("o", Height::Mid, Backness::Front, true, true),
       new Vowel("ʊ", Height::High, Backness::Front, false, true)},
      {new Consonant("d", Place::Alveolar, Manner::Plosive, true)});
  auto* barcode = new Word({*bar, *code});
  std::cout << barcode->Symbols() << std::endl;
}
