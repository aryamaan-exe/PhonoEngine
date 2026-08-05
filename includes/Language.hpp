#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <functional>
#include <memory>
#include <optional>
#include <set>
#include <unordered_map>

#include "Consonant.hpp"
#include "Phoneme.hpp"
#include "Rule.hpp"
#include "Vowel.hpp"
#include "Word.hpp"

using TokenConverter =
    std::function<std::optional<Symbol>(const std::wstring&)>;
using SymbolMap = std::unordered_map<Symbol, std::unique_ptr<Phoneme>>;

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
  void AddRule(const Rule& rule);
  void AddSyllabicConsonant(const Symbol& symbol);
  void AddDiphthong(const Symbol& first, const Symbol& second);
  void SetTokenConverter(TokenConverter converter);
  static std::wstring Utf8ToWide(const std::string& utf8);

  bool IsNucleusCapable(const Phoneme* phoneme) const;
  bool FormsDiphthongWith(const Symbol& prev, const Symbol& next) const;

  ValidationResult Validate(const Word& word) const;
  Word BuildWordFromSymbols(std::vector<Symbol>& word);
  Phoneme* GetPhonemeFromSymbol(const Symbol& symbol) const;
  std::vector<Syllable> GetSyllablesFromTokens(
      const std::vector<std::wstring>& tokens) const;

  friend std::wostream& operator<<(std::wostream& os, Language& language);

private:
  std::set<Symbol> syllabic_consonants_;
  std::set<std::pair<Symbol, Symbol>> diphthongs_;
  SymbolMap symbols_;
  std::vector<std::unique_ptr<Rule>> rules_;
  TokenConverter converter_;
  inline static const SymbolMap kIPAChart{[]() {
    SymbolMap chart;
    chart.emplace(L"p",
                  std::make_unique<Consonant>(
                      L"p", Place::Bilabial, Manner::Plosive, false));
    chart.emplace(L"b",
                  std::make_unique<Consonant>(
                      L"b", Place::Bilabial, Manner::Plosive, true));
    chart.emplace(L"t",
                  std::make_unique<Consonant>(
                      L"t", Place::Alveolar, Manner::Plosive, false));
    chart.emplace(L"d",
                  std::make_unique<Consonant>(
                      L"d", Place::Alveolar, Manner::Plosive, true));
    chart.emplace(L"ʈ",
                  std::make_unique<Consonant>(
                      L"ʈ", Place::Retroflex, Manner::Plosive, false));
    chart.emplace(L"ɖ",
                  std::make_unique<Consonant>(
                      L"ɖ", Place::Retroflex, Manner::Plosive, true));
    chart.emplace(L"c",
                  std::make_unique<Consonant>(
                      L"c", Place::Palatal, Manner::Plosive, false));
    chart.emplace(L"ɟ",
                  std::make_unique<Consonant>(
                      L"ɟ", Place::Palatal, Manner::Plosive, true));
    chart.emplace(L"k",
                  std::make_unique<Consonant>(
                      L"k", Place::Velar, Manner::Plosive, false));
    chart.emplace(
        L"g",
        std::make_unique<Consonant>(L"g", Place::Velar, Manner::Plosive, true));
    chart.emplace(L"q",
                  std::make_unique<Consonant>(
                      L"q", Place::Uvular, Manner::Plosive, false));
    chart.emplace(L"ɢ",
                  std::make_unique<Consonant>(
                      L"ɢ", Place::Uvular, Manner::Plosive, true));
    chart.emplace(L"ʔ",
                  std::make_unique<Consonant>(
                      L"ʔ", Place::Glottal, Manner::Plosive, false));

    chart.emplace(L"m",
                  std::make_unique<Consonant>(
                      L"m", Place::Bilabial, Manner::Nasal, true));
    chart.emplace(L"ɱ",
                  std::make_unique<Consonant>(
                      L"ɱ", Place::Labiodental, Manner::Nasal, true));
    chart.emplace(L"n",
                  std::make_unique<Consonant>(
                      L"n", Place::Alveolar, Manner::Nasal, true));
    chart.emplace(L"ɳ",
                  std::make_unique<Consonant>(
                      L"ɳ", Place::Retroflex, Manner::Nasal, true));
    chart.emplace(
        L"ɲ",
        std::make_unique<Consonant>(L"ɲ", Place::Palatal, Manner::Nasal, true));
    chart.emplace(
        L"ŋ",
        std::make_unique<Consonant>(L"ŋ", Place::Velar, Manner::Nasal, true));
    chart.emplace(
        L"ɴ",
        std::make_unique<Consonant>(L"ɴ", Place::Uvular, Manner::Nasal, true));

    chart.emplace(L"ʙ",
                  std::make_unique<Consonant>(
                      L"ʙ", Place::Bilabial, Manner::Trill, true));
    chart.emplace(L"r",
                  std::make_unique<Consonant>(
                      L"r", Place::Alveolar, Manner::Trill, true));
    chart.emplace(
        L"ʀ",
        std::make_unique<Consonant>(L"ʀ", Place::Uvular, Manner::Trill, true));

    chart.emplace(L"ⱱ",
                  std::make_unique<Consonant>(
                      L"ⱱ", Place::Labiodental, Manner::Tap, true));
    chart.emplace(
        L"ɾ",
        std::make_unique<Consonant>(L"ɾ", Place::Alveolar, Manner::Tap, true));
    chart.emplace(
        L"ɽ",
        std::make_unique<Consonant>(L"ɽ", Place::Retroflex, Manner::Tap, true));

    chart.emplace(L"ɸ",
                  std::make_unique<Consonant>(
                      L"ɸ", Place::Bilabial, Manner::Fricative, false));
    chart.emplace(L"β",
                  std::make_unique<Consonant>(
                      L"β", Place::Bilabial, Manner::Fricative, true));
    chart.emplace(L"f",
                  std::make_unique<Consonant>(
                      L"f", Place::Labiodental, Manner::Fricative, false));
    chart.emplace(L"v",
                  std::make_unique<Consonant>(
                      L"v", Place::Labiodental, Manner::Fricative, true));
    chart.emplace(L"θ",
                  std::make_unique<Consonant>(
                      L"θ", Place::Dental, Manner::Fricative, false));
    chart.emplace(L"ð",
                  std::make_unique<Consonant>(
                      L"ð", Place::Dental, Manner::Fricative, true));
    chart.emplace(L"s",
                  std::make_unique<Consonant>(
                      L"s", Place::Alveolar, Manner::Fricative, false));
    chart.emplace(L"z",
                  std::make_unique<Consonant>(
                      L"z", Place::Alveolar, Manner::Fricative, true));
    chart.emplace(L"ʃ",
                  std::make_unique<Consonant>(
                      L"ʃ", Place::Postalveolar, Manner::Fricative, false));
    chart.emplace(L"ʒ",
                  std::make_unique<Consonant>(
                      L"ʒ", Place::Postalveolar, Manner::Fricative, true));
    chart.emplace(L"ʂ",
                  std::make_unique<Consonant>(
                      L"ʂ", Place::Retroflex, Manner::Fricative, false));
    chart.emplace(L"ʐ",
                  std::make_unique<Consonant>(
                      L"ʐ", Place::Retroflex, Manner::Fricative, true));
    chart.emplace(L"ç",
                  std::make_unique<Consonant>(
                      L"ç", Place::Palatal, Manner::Fricative, false));
    chart.emplace(L"ʝ",
                  std::make_unique<Consonant>(
                      L"ʝ", Place::Palatal, Manner::Fricative, true));
    chart.emplace(L"x",
                  std::make_unique<Consonant>(
                      L"x", Place::Velar, Manner::Fricative, false));
    chart.emplace(L"ɣ",
                  std::make_unique<Consonant>(
                      L"ɣ", Place::Velar, Manner::Fricative, true));
    chart.emplace(L"χ",
                  std::make_unique<Consonant>(
                      L"χ", Place::Uvular, Manner::Fricative, false));
    chart.emplace(L"ʁ",
                  std::make_unique<Consonant>(
                      L"ʁ", Place::Uvular, Manner::Fricative, true));
    chart.emplace(L"ħ",
                  std::make_unique<Consonant>(
                      L"ħ", Place::Pharyngeal, Manner::Fricative, false));
    chart.emplace(L"ʕ",
                  std::make_unique<Consonant>(
                      L"ʕ", Place::Pharyngeal, Manner::Fricative, true));
    chart.emplace(L"h",
                  std::make_unique<Consonant>(
                      L"h", Place::Glottal, Manner::Fricative, false));
    chart.emplace(L"ɦ",
                  std::make_unique<Consonant>(
                      L"ɦ", Place::Glottal, Manner::Fricative, true));

    chart.emplace(L"w",
                  std::make_unique<Consonant>(
                      L"w", Place::Bilabial, Manner::Approximant, true));
    chart.emplace(L"w",
                  std::make_unique<Consonant>(
                      L"w", Place::Bilabial, Manner::Approximant, false));
    chart.emplace(L"ʋ",
                  std::make_unique<Consonant>(
                      L"ʋ", Place::Labiodental, Manner::Approximant, true));
    chart.emplace(L"ɹ",
                  std::make_unique<Consonant>(
                      L"ɹ", Place::Alveolar, Manner::Approximant, true));
    chart.emplace(L"ɻ",
                  std::make_unique<Consonant>(
                      L"ɻ", Place::Retroflex, Manner::Approximant, true));
    chart.emplace(L"j",
                  std::make_unique<Consonant>(
                      L"j", Place::Palatal, Manner::Approximant, true));
    chart.emplace(L"ɰ",
                  std::make_unique<Consonant>(
                      L"ɰ", Place::Velar, Manner::Approximant, true));

    chart.emplace(L"t͡s",
                  std::make_unique<Consonant>(
                      L"t͡s", Place::Alveolar, Manner::Affricate, false));
    chart.emplace(L"d͡z",
                  std::make_unique<Consonant>(
                      L"d͡z", Place::Alveolar, Manner::Affricate, true));
    chart.emplace(L"t͡ʃ",
                  std::make_unique<Consonant>(
                      L"t͡ʃ", Place::Postalveolar, Manner::Affricate, false));
    chart.emplace(L"d͡ʒ",
                  std::make_unique<Consonant>(
                      L"d͡ʒ", Place::Postalveolar, Manner::Affricate, true));

    chart.emplace(L"l",
                  std::make_unique<Consonant>(
                      L"l", Place::Alveolar, Manner::LateralApproximant, true));
    chart.emplace(
        L"ɭ",
        std::make_unique<Consonant>(
            L"ɭ", Place::Retroflex, Manner::LateralApproximant, true));
    chart.emplace(L"ʎ",
                  std::make_unique<Consonant>(
                      L"ʎ", Place::Palatal, Manner::LateralApproximant, true));
    chart.emplace(L"ʟ",
                  std::make_unique<Consonant>(
                      L"ʟ", Place::Velar, Manner::LateralApproximant, true));

    chart.emplace(L"ɬ",
                  std::make_unique<Consonant>(
                      L"ɬ", Place::Alveolar, Manner::LateralFricative, false));
    chart.emplace(L"ɮ",
                  std::make_unique<Consonant>(
                      L"ɮ", Place::Alveolar, Manner::LateralFricative, true));

    chart.emplace(L"i",
                  std::make_unique<Vowel>(
                      L"i", Height::High, Backness::Front, true, false));
    chart.emplace(L"y",
                  std::make_unique<Vowel>(
                      L"y", Height::High, Backness::Front, true, true));
    chart.emplace(L"ɨ",
                  std::make_unique<Vowel>(
                      L"ɨ", Height::High, Backness::Central, true, false));
    chart.emplace(L"ʉ",
                  std::make_unique<Vowel>(
                      L"ʉ", Height::High, Backness::Central, true, true));
    chart.emplace(L"ɯ",
                  std::make_unique<Vowel>(
                      L"ɯ", Height::High, Backness::Back, true, false));
    chart.emplace(L"u",
                  std::make_unique<Vowel>(
                      L"u", Height::High, Backness::Back, true, true));

    chart.emplace(L"ɪ",
                  std::make_unique<Vowel>(
                      L"ɪ", Height::High, Backness::Front, false, false));
    chart.emplace(L"ʏ",
                  std::make_unique<Vowel>(
                      L"ʏ", Height::High, Backness::Front, false, true));
    chart.emplace(L"ʊ",
                  std::make_unique<Vowel>(
                      L"ʊ", Height::High, Backness::Back, false, true));

    chart.emplace(L"e",
                  std::make_unique<Vowel>(
                      L"e", Height::Mid, Backness::Front, true, false));
    chart.emplace(L"ø",
                  std::make_unique<Vowel>(
                      L"ø", Height::Mid, Backness::Front, true, true));
    chart.emplace(L"ɘ",
                  std::make_unique<Vowel>(
                      L"ɘ", Height::Mid, Backness::Central, true, false));
    chart.emplace(L"ɵ",
                  std::make_unique<Vowel>(
                      L"ɵ", Height::Mid, Backness::Central, true, true));
    chart.emplace(L"ɤ",
                  std::make_unique<Vowel>(
                      L"ɤ", Height::Mid, Backness::Back, true, false));
    chart.emplace(
        L"o",
        std::make_unique<Vowel>(L"o", Height::Mid, Backness::Back, true, true));

    chart.emplace(L"ə",
                  std::make_unique<Vowel>(
                      L"ə", Height::Mid, Backness::Central, false, false));

    chart.emplace(L"ɛ",
                  std::make_unique<Vowel>(
                      L"ɛ", Height::Mid, Backness::Front, false, false));
    chart.emplace(L"œ",
                  std::make_unique<Vowel>(
                      L"œ", Height::Mid, Backness::Front, false, true));
    chart.emplace(L"ɜ",
                  std::make_unique<Vowel>(
                      L"ɜ", Height::Mid, Backness::Central, false, false));
    chart.emplace(L"ɞ",
                  std::make_unique<Vowel>(
                      L"ɞ", Height::Mid, Backness::Central, false, true));
    chart.emplace(L"ʌ",
                  std::make_unique<Vowel>(
                      L"ʌ", Height::Mid, Backness::Back, false, false));
    chart.emplace(L"ɔ",
                  std::make_unique<Vowel>(
                      L"ɔ", Height::Mid, Backness::Back, false, true));

    chart.emplace(L"æ",
                  std::make_unique<Vowel>(
                      L"æ", Height::Low, Backness::Front, false, false));
    chart.emplace(L"ɐ",
                  std::make_unique<Vowel>(
                      L"ɐ", Height::Low, Backness::Central, false, false));

    chart.emplace(L"a",
                  std::make_unique<Vowel>(
                      L"a", Height::Low, Backness::Front, true, false));
    chart.emplace(L"ɶ",
                  std::make_unique<Vowel>(
                      L"ɶ", Height::Low, Backness::Front, true, true));
    chart.emplace(L"ɑ",
                  std::make_unique<Vowel>(
                      L"ɑ", Height::Low, Backness::Back, true, false));
    chart.emplace(
        L"ɒ",
        std::make_unique<Vowel>(L"ɒ", Height::Low, Backness::Back, true, true));
    return chart;
  }()};
};

#endif