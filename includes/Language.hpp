#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <functional>
#include <memory>
#include <optional>
#include <unordered_map>

#include "Consonant.hpp"
#include "Phoneme.hpp"
#include "Rule.hpp"
#include "Vowel.hpp"
#include "Word.hpp"

using Inventory = std::vector<std::unique_ptr<Phoneme>>;
using TokenConverter =
    std::function<std::optional<Symbol>(const std::wstring&)>;
using SymbolMap = std::unordered_map<Symbol, Phoneme*>;

struct ValidationResult {
  bool valid;
  std::wstring reason;
};

class Language {
public:
  Language() = default;
  Language(const std::string& filename);
  void AddPhoneme(std::unique_ptr<Phoneme> phoneme);
  void AddIPAPhoneme(const Symbol& ipa_symbol);
  void AddRule(Rule* rule);
  void SetTokenConverter(TokenConverter converter);

  ValidationResult Validate(const Word& word);
  Word BuildWordFromSymbols(std::vector<Symbol>& word);
  Phoneme* GetPhonemeFromSymbol(const Symbol& symbol);
  std::vector<Syllable> GetSyllablesFromTokens(
      const std::vector<std::wstring>& tokens);

private:
  Inventory inventory_;
  SymbolMap symbols_;
  std::vector<Rule*> rules_;
  TokenConverter converter_;
  inline static const SymbolMap kIPAChart{
      {L"p", new Consonant{L"p", Place::Bilabial, Manner::Plosive, false}},
      {L"b", new Consonant{L"b", Place::Bilabial, Manner::Plosive, true}},
      {L"t", new Consonant{L"t", Place::Alveolar, Manner::Plosive, false}},
      {L"d", new Consonant{L"d", Place::Alveolar, Manner::Plosive, true}},
      {L"ʈ", new Consonant{L"ʈ", Place::Retroflex, Manner::Plosive, false}},
      {L"ɖ", new Consonant{L"ɖ", Place::Retroflex, Manner::Plosive, true}},
      {L"c", new Consonant{L"c", Place::Palatal, Manner::Plosive, false}},
      {L"ɟ", new Consonant{L"ɟ", Place::Palatal, Manner::Plosive, true}},
      {L"k", new Consonant{L"k", Place::Velar, Manner::Plosive, false}},
      {L"g", new Consonant{L"g", Place::Velar, Manner::Plosive, true}},
      {L"q", new Consonant{L"q", Place::Uvular, Manner::Plosive, false}},
      {L"ɢ", new Consonant{L"ɢ", Place::Uvular, Manner::Plosive, true}},
      {L"ʔ", new Consonant{L"ʔ", Place::Glottal, Manner::Plosive, false}},

      {L"m", new Consonant{L"m", Place::Bilabial, Manner::Nasal, true}},
      {L"ɱ", new Consonant{L"ɱ", Place::Labiodental, Manner::Nasal, true}},
      {L"n", new Consonant{L"n", Place::Alveolar, Manner::Nasal, true}},
      {L"ɳ", new Consonant{L"ɳ", Place::Retroflex, Manner::Nasal, true}},
      {L"ɲ", new Consonant{L"ɲ", Place::Palatal, Manner::Nasal, true}},
      {L"ŋ", new Consonant{L"ŋ", Place::Velar, Manner::Nasal, true}},
      {L"ɴ", new Consonant{L"ɴ", Place::Uvular, Manner::Nasal, true}},

      {L"ʙ", new Consonant{L"ʙ", Place::Bilabial, Manner::Trill, true}},
      {L"r", new Consonant{L"r", Place::Alveolar, Manner::Trill, true}},
      {L"ʀ", new Consonant{L"ʀ", Place::Uvular, Manner::Trill, true}},

      {L"ⱱ", new Consonant{L"ⱱ", Place::Labiodental, Manner::Tap, true}},
      {L"ɾ", new Consonant{L"ɾ", Place::Alveolar, Manner::Tap, true}},
      {L"ɽ", new Consonant{L"ɽ", Place::Retroflex, Manner::Tap, true}},

      {L"ɸ", new Consonant{L"ɸ", Place::Bilabial, Manner::Fricative, false}},
      {L"β", new Consonant{L"β", Place::Bilabial, Manner::Fricative, true}},
      {L"f", new Consonant{L"f", Place::Labiodental, Manner::Fricative, false}},
      {L"v", new Consonant{L"v", Place::Labiodental, Manner::Fricative, true}},
      {L"θ", new Consonant{L"θ", Place::Dental, Manner::Fricative, false}},
      {L"ð", new Consonant{L"ð", Place::Dental, Manner::Fricative, true}},
      {L"s", new Consonant{L"s", Place::Alveolar, Manner::Fricative, false}},
      {L"z", new Consonant{L"z", Place::Alveolar, Manner::Fricative, true}},
      {L"ʃ",
       new Consonant{L"ʃ", Place::Postalveolar, Manner::Fricative, false}},
      {L"ʒ", new Consonant{L"ʒ", Place::Postalveolar, Manner::Fricative, true}},
      {L"ʂ", new Consonant{L"ʂ", Place::Retroflex, Manner::Fricative, false}},
      {L"ʐ", new Consonant{L"ʐ", Place::Retroflex, Manner::Fricative, true}},
      {L"ç", new Consonant{L"ç", Place::Palatal, Manner::Fricative, false}},
      {L"ʝ", new Consonant{L"ʝ", Place::Palatal, Manner::Fricative, true}},
      {L"x", new Consonant{L"x", Place::Velar, Manner::Fricative, false}},
      {L"ɣ", new Consonant{L"ɣ", Place::Velar, Manner::Fricative, true}},
      {L"χ", new Consonant{L"χ", Place::Uvular, Manner::Fricative, false}},
      {L"ʁ", new Consonant{L"ʁ", Place::Uvular, Manner::Fricative, true}},
      {L"ħ", new Consonant{L"ħ", Place::Pharyngeal, Manner::Fricative, false}},
      {L"ʕ", new Consonant{L"ʕ", Place::Pharyngeal, Manner::Fricative, true}},
      {L"h", new Consonant{L"h", Place::Glottal, Manner::Fricative, false}},
      {L"ɦ", new Consonant{L"ɦ", Place::Glottal, Manner::Fricative, true}},

      {L"ʋ",
       new Consonant{L"ʋ", Place::Labiodental, Manner::Approximant, true}},
      {L"ɹ", new Consonant{L"ɹ", Place::Alveolar, Manner::Approximant, true}},
      {L"ɻ", new Consonant{L"ɻ", Place::Retroflex, Manner::Approximant, true}},
      {L"j", new Consonant{L"j", Place::Palatal, Manner::Approximant, true}},
      {L"ɰ", new Consonant{L"ɰ", Place::Velar, Manner::Approximant, true}},

      {L"t͡s", new Consonant{L"t͡s", Place::Alveolar, Manner::Affricate, false}},
      {L"d͡z", new Consonant{L"d͡z", Place::Alveolar, Manner::Affricate, true}},
      {L"t͡ʃ",
       new Consonant{L"t͡ʃ", Place::Postalveolar, Manner::Affricate, false}},
      {L"d͡ʒ",
       new Consonant{L"d͡ʒ", Place::Postalveolar, Manner::Affricate, true}},

      {L"l",
       new Consonant{L"l", Place::Alveolar, Manner::LateralApproximant, true}},
      {L"ɭ",
       new Consonant{L"ɭ", Place::Retroflex, Manner::LateralApproximant, true}},
      {L"ʎ",
       new Consonant{L"ʎ", Place::Palatal, Manner::LateralApproximant, true}},
      {L"ʟ",
       new Consonant{L"ʟ", Place::Velar, Manner::LateralApproximant, true}},

      {L"ɬ",
       new Consonant{L"ɬ", Place::Alveolar, Manner::LateralFricative, false}},
      {L"ɮ",
       new Consonant{L"ɮ", Place::Alveolar, Manner::LateralFricative, true}},

      {L"i", new Vowel{L"i", Height::High, Backness::Front, true, false}},
      {L"y", new Vowel{L"y", Height::High, Backness::Front, true, true}},
      {L"ɨ", new Vowel{L"ɨ", Height::High, Backness::Central, true, false}},
      {L"ʉ", new Vowel{L"ʉ", Height::High, Backness::Central, true, true}},
      {L"ɯ", new Vowel{L"ɯ", Height::High, Backness::Back, true, false}},
      {L"u", new Vowel{L"u", Height::High, Backness::Back, true, true}},

      {L"ɪ", new Vowel{L"ɪ", Height::High, Backness::Front, false, false}},
      {L"ʏ", new Vowel{L"ʏ", Height::High, Backness::Front, false, true}},
      {L"ʊ", new Vowel{L"ʊ", Height::High, Backness::Back, false, true}},

      {L"e", new Vowel{L"e", Height::Mid, Backness::Front, true, false}},
      {L"ø", new Vowel{L"ø", Height::Mid, Backness::Front, true, true}},
      {L"ɘ", new Vowel{L"ɘ", Height::Mid, Backness::Central, true, false}},
      {L"ɵ", new Vowel{L"ɵ", Height::Mid, Backness::Central, true, true}},
      {L"ɤ", new Vowel{L"ɤ", Height::Mid, Backness::Back, true, false}},
      {L"o", new Vowel{L"o", Height::Mid, Backness::Back, true, true}},

      {L"ə", new Vowel{L"ə", Height::Mid, Backness::Central, false, false}},

      {L"ɛ", new Vowel{L"ɛ", Height::Mid, Backness::Front, false, false}},
      {L"œ", new Vowel{L"œ", Height::Mid, Backness::Front, false, true}},
      {L"ɜ", new Vowel{L"ɜ", Height::Mid, Backness::Central, false, false}},
      {L"ɞ", new Vowel{L"ɞ", Height::Mid, Backness::Central, false, true}},
      {L"ʌ", new Vowel{L"ʌ", Height::Mid, Backness::Back, false, false}},
      {L"ɔ", new Vowel{L"ɔ", Height::Mid, Backness::Back, false, true}},

      {L"æ", new Vowel{L"æ", Height::Low, Backness::Front, false, false}},
      {L"ɐ", new Vowel{L"ɐ", Height::Low, Backness::Central, false, false}},

      {L"a", new Vowel{L"a", Height::Low, Backness::Front, true, false}},
      {L"ɶ", new Vowel{L"ɶ", Height::Low, Backness::Front, true, true}},
      {L"ɑ", new Vowel{L"ɑ", Height::Low, Backness::Back, true, false}},
      {L"ɒ", new Vowel{L"ɒ", Height::Low, Backness::Back, true, true}},
  };
};

#endif