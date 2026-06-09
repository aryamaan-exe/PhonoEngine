#include <iostream>
#include <vector>

#include "Consonant.hpp"
#include "Language.hpp"
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

  Language English;

  English.AddPhoneme(new Consonant("p", Bilabial, Plosive, false));
  English.AddPhoneme(new Consonant("b", Bilabial, Plosive, true));
  English.AddPhoneme(new Consonant("t", Alveolar, Plosive, false));
  English.AddPhoneme(new Consonant("d", Alveolar, Plosive, true));
  English.AddPhoneme(new Consonant("k", Velar, Plosive, false));
  English.AddPhoneme(new Consonant("g", Velar, Plosive, true));

  English.AddPhoneme(new Consonant("m", Bilabial, Nasal, true));
  English.AddPhoneme(new Consonant("n", Alveolar, Nasal, true));
  English.AddPhoneme(new Consonant("ŋ", Velar, Nasal, true));

  English.AddPhoneme(new Consonant("f", Labiodental, Fricative, false));
  English.AddPhoneme(new Consonant("v", Labiodental, Fricative, true));
  English.AddPhoneme(new Consonant("θ", Dental, Fricative, false));
  English.AddPhoneme(new Consonant("ð", Dental, Fricative, true));
  English.AddPhoneme(new Consonant("s", Alveolar, Fricative, false));
  English.AddPhoneme(new Consonant("z", Alveolar, Fricative, true));
  English.AddPhoneme(new Consonant("ʃ", Postalveolar, Fricative, false));
  English.AddPhoneme(new Consonant("ʒ", Postalveolar, Fricative, true));
  English.AddPhoneme(new Consonant("h", Glottal, Fricative, false));

  English.AddPhoneme(new Consonant("l", Alveolar, Approximant, true));
  English.AddPhoneme(new Consonant("r", Alveolar, Approximant, true));
  English.AddPhoneme(new Consonant("j", Palatal, Approximant, true));
  English.AddPhoneme(new Consonant("w", Bilabial, Approximant, true));

  English.AddPhoneme(new Vowel("i", High, Front, true, false));
  English.AddPhoneme(new Vowel("ɪ", High, Front, false, false));
  English.AddPhoneme(new Vowel("e", Mid, Front, true, false));
  English.AddPhoneme(new Vowel("ɛ", Mid, Front, false, false));
  English.AddPhoneme(new Vowel("æ", Low, Front, false, false));

  English.AddPhoneme(new Vowel("ə", Mid, Central, false, false));
  English.AddPhoneme(new Vowel("ʌ", Mid, Central, false, false));

  English.AddPhoneme(new Vowel("u", High, Back, true, true));
  English.AddPhoneme(new Vowel("ʊ", High, Back, false, true));
  English.AddPhoneme(new Vowel("ɔ", Mid, Back, false, true));
  English.AddPhoneme(new Vowel("ɑ", Low, Back, false, false));

  auto* nucleus_exists = new Rule(
      "Nucleus must exist",
      [](const std::vector<Phoneme*>& nucleus) { return !nucleus.empty(); });

  auto* nucleus_only_vowels =
      new Rule("Nucleus must contain only vowels",
               [](const std::vector<Phoneme*>& nucleus) {
                 for (Phoneme* p : nucleus) {
                   if (p->GetType() != kVowel) return false;
                 }
                 return true;
               });

  auto* onset_only_consonants =
      new Rule("Onset must contain only consonants",
               [](const std::vector<Phoneme*>& onset) {
                 for (Phoneme* p : onset) {
                   if (p->GetType() != kConsonant) return false;
                 }
                 return true;
               });

  auto* coda_only_consonants = new Rule("Coda must contain only consonants",
                                        [](const std::vector<Phoneme*>& coda) {
                                          for (Phoneme* p : coda) {
                                            if (p->GetType() != kConsonant)
                                              return false;
                                          }
                                          return true;
                                        });

  auto* max_onset_size = new Rule(
      "Onset may have at most 3 consonants",
      [](const std::vector<Phoneme*>& onset) { return onset.size() <= 3; });

  auto* max_coda_size = new Rule(
      "Coda may have at most 4 consonants",
      [](const std::vector<Phoneme*>& coda) { return coda.size() <= 4; });

  auto* max_nucleus_size = new Rule(
      "Nucleus may have at most 2 vowels",
      [](const std::vector<Phoneme*>& nucleus) { return nucleus.size() <= 2; });

  auto* three_consonant_onset_rule =
      new Rule("Three-consonant English onsets must start with s",
               [](const std::vector<Phoneme*>& onset) {
                 if (onset.size() != 3) return true;
                 return onset[0]->GetSymbol() == "s";
               });

  auto* english_onset_ng_rule = new Rule(
      "Syllables cannot begin with ng", [](const std::vector<Phoneme*>& onset) {
        if (onset.empty()) return true;
        return onset[0]->GetSymbol() != "ŋ";
      });

  auto* coda_h_rule = new Rule("Syllables cannot end with h",
                               [](const std::vector<Phoneme*>& coda) {
                                 if (coda.empty()) return true;
                                 return coda.back()->GetSymbol() != "h";
                               });

  auto* no_empty_syllable_rule =
      new Rule("Syllable cannot be completely empty",
               [](const std::vector<Phoneme*>& part) { return !part.empty(); });

  English.AddRule(nucleus_exists);
  English.AddRule(nucleus_only_vowels);
  English.AddRule(onset_only_consonants);
  English.AddRule(coda_only_consonants);

  English.AddRule(max_onset_size);
  English.AddRule(max_coda_size);
  English.AddRule(max_nucleus_size);

  English.AddRule(three_consonant_onset_rule);
  English.AddRule(english_onset_ng_rule);

  English.AddRule(coda_h_rule);

  
}
