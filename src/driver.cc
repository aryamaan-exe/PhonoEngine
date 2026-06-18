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

  auto* bar = new Syllable{o, n, c};
  auto* rb = new Syllable{c, e, o};
  std::cout << bar->Symbols() << std::endl;

  auto* rule = new Rule(
      "Nucleus must exist",
      RuleType::Nucleus,
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

  English.AddPhoneme(
      new Consonant("p", Place::Bilabial, Manner::Plosive, false));
  English.AddPhoneme(
      new Consonant("b", Place::Bilabial, Manner::Plosive, true));
  English.AddPhoneme(
      new Consonant("t", Place::Alveolar, Manner::Plosive, false));
  English.AddPhoneme(
      new Consonant("d", Place::Alveolar, Manner::Plosive, true));
  English.AddPhoneme(new Consonant("k", Place::Velar, Manner::Plosive, false));
  English.AddPhoneme(new Consonant("g", Place::Velar, Manner::Plosive, true));

  English.AddPhoneme(new Consonant("m", Place::Bilabial, Manner::Nasal, true));
  English.AddPhoneme(new Consonant("n", Place::Alveolar, Manner::Nasal, true));
  English.AddPhoneme(new Consonant("ŋ", Place::Velar, Manner::Nasal, true));

  English.AddPhoneme(
      new Consonant("f", Place::Labiodental, Manner::Fricative, false));
  English.AddPhoneme(
      new Consonant("v", Place::Labiodental, Manner::Fricative, true));
  English.AddPhoneme(
      new Consonant("θ", Place::Dental, Manner::Fricative, false));
  English.AddPhoneme(
      new Consonant("ð", Place::Dental, Manner::Fricative, true));
  English.AddPhoneme(
      new Consonant("s", Place::Alveolar, Manner::Fricative, false));
  English.AddPhoneme(
      new Consonant("z", Place::Alveolar, Manner::Fricative, true));
  English.AddPhoneme(
      new Consonant("ʃ", Place::Postalveolar, Manner::Fricative, false));
  English.AddPhoneme(
      new Consonant("ʒ", Place::Postalveolar, Manner::Fricative, true));
  English.AddPhoneme(
      new Consonant("h", Place::Glottal, Manner::Fricative, false));

  English.AddPhoneme(
      new Consonant("l", Place::Alveolar, Manner::Approximant, true));
  English.AddPhoneme(
      new Consonant("ɹ", Place::Alveolar, Manner::Approximant, true));
  English.AddPhoneme(
      new Consonant("j", Place::Palatal, Manner::Approximant, true));
  English.AddPhoneme(
      new Consonant("w", Place::Bilabial, Manner::Approximant, true));

  English.AddPhoneme(
      new Vowel("i", Height::High, Backness::Front, true, false));
  English.AddPhoneme(
      new Vowel("ɪ", Height::High, Backness::Front, false, false));
  English.AddPhoneme(new Vowel("e", Height::Mid, Backness::Front, true, false));
  English.AddPhoneme(
      new Vowel("ɛ", Height::Mid, Backness::Front, false, false));
  English.AddPhoneme(
      new Vowel("æ", Height::Low, Backness::Front, false, false));

  English.AddPhoneme(
      new Vowel("ə", Height::Mid, Backness::Central, false, false));
  English.AddPhoneme(
      new Vowel("ʌ", Height::Mid, Backness::Central, false, false));

  English.AddPhoneme(new Vowel("u", Height::High, Backness::Back, true, true));
  English.AddPhoneme(new Vowel("ʊ", Height::High, Backness::Back, false, true));
  English.AddPhoneme(new Vowel("ɔ", Height::Mid, Backness::Back, false, true));
  English.AddPhoneme(new Vowel("ɑ", Height::Low, Backness::Back, false, false));

  auto* nucleus_exists = new Rule(
      "Nucleus must exist",
      RuleType::Nucleus,
      [](const std::vector<Phoneme*>& nucleus) { return !nucleus.empty(); });

  auto* nucleus_only_vowels =
      new Rule("Nucleus must contain only vowels",
               RuleType::Nucleus,
               [](const std::vector<Phoneme*>& nucleus) {
                 for (Phoneme* p : nucleus) {
                   if (p->GetType() != PhonemeType::kVowel) return false;
                 }
                 return true;
               });

  auto* onset_only_consonants =
      new Rule("Onset must contain only consonants",
               RuleType::Onset,
               [](const std::vector<Phoneme*>& onset) {
                 for (Phoneme* p : onset) {
                   if (p->GetType() != PhonemeType::kConsonant) return false;
                 }
                 return true;
               });

  auto* coda_only_consonants =
      new Rule("Coda must contain only consonants",
               RuleType::Coda,
               [](const std::vector<Phoneme*>& coda) {
                 for (Phoneme* p : coda) {
                   if (p->GetType() != PhonemeType::kConsonant) return false;
                 }
                 return true;
               });

  auto* max_onset_size = new Rule(
      "Onset may have at most 3 consonants",
      RuleType::Onset,
      [](const std::vector<Phoneme*>& onset) { return onset.size() <= 3; });

  auto* max_coda_size = new Rule(
      "Coda may have at most 4 consonants",
      RuleType::Coda,
      [](const std::vector<Phoneme*>& coda) { return coda.size() <= 4; });

  auto* max_nucleus_size = new Rule(
      "Nucleus may have at most 2 vowels",
      RuleType::Nucleus,
      [](const std::vector<Phoneme*>& nucleus) { return nucleus.size() <= 2; });

  auto* three_consonant_onset_rule =
      new Rule("Three-consonant English onsets must start with s",
               RuleType::Onset,
               [](const std::vector<Phoneme*>& onset) {
                 if (onset.size() != 3) return true;
                 return onset[0]->GetSymbol() == "s";
               });

  auto* english_onset_ng_rule =
      new Rule("Syllables cannot begin with ng",
               RuleType::Onset,
               [](const std::vector<Phoneme*>& onset) {
                 if (onset.empty()) return true;
                 return onset[0]->GetSymbol() != "ŋ";
               });

  auto* coda_h_rule = new Rule("Syllables cannot end with h",
                               RuleType::Coda,
                               [](const std::vector<Phoneme*>& coda) {
                                 if (coda.empty()) return true;
                                 return coda.back()->GetSymbol() != "h";
                               });

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

  try {
    std::cout << English.Validate(*barcode) << std::endl;
    auto* invalid = new Word({*rb, *code});
    std::cout << English.Validate(*invalid) << std::endl;
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }

  std::vector<std::string> w = {"b", ".", "ɑ", ".", "ɹ", "."};
  Word from_symbol = English.BuildWordFromSymbols(w);
  std::cout << from_symbol.Symbols() << std::endl;
}
