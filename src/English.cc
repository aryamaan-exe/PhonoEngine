#include "English.hpp"

constexpr std::array<std::pair<std::string_view, Symbol>, 39> kPhoneticMap{{
    {"AA", L"ɑ"}, {"AE", L"æ"}, {"AH", L"ʌ"}, {"AO", L"ɔ"}, {"AW", L"a"},
    {"AY", L"a"}, {"EH", L"ɛ"}, {"ER", L"ɝ"}, {"EY", L"e"}, {"IH", L"ɪ"},
    {"IY", L"i"}, {"OW", L"o"}, {"OY", L"ɔ"}, {"UH", L"ʊ"}, {"UW", L"u"},

    {"B", L"b"},  {"CH", L"ʧ"}, {"D", L"d"},  {"DH", L"ð"}, {"F", L"f"},
    {"G", L"ɡ"},  {"HH", L"h"}, {"JH", L"ʤ"}, {"K", L"k"},  {"L", L"l"},
    {"M", L"m"},  {"N", L"n"},  {"NG", L"ŋ"}, {"P", L"p"},  {"R", L"ɹ"},
    {"S", L"s"},  {"SH", L"ʃ"}, {"T", L"t"},  {"TH", L"θ"}, {"V", L"v"},
    {"W", L"w"},  {"Y", L"j"},  {"Z", L"z"},  {"ZH", L"ʒ"},
}};

constexpr Symbol Lookup(std::string_view key) {
  const auto* it = std::find_if(kPhoneticMap.begin(),
                                kPhoneticMap.end(),
                                [&](auto& p) { return p.first == key; });
  return it != kPhoneticMap.end() ? it->second : L"";
}

// NOLINTBEGIN
const Language EnglishLang::BuildEnglish() {
  Language English;

  English.AddPhoneme(std::make_unique<Consonant>(
      L"p", Place::Bilabial, Manner::Plosive, false));
  English.AddPhoneme(std::make_unique<Consonant>(
      L"b", Place::Bilabial, Manner::Plosive, true));
  English.AddPhoneme(std::make_unique<Consonant>(
      L"t", Place::Alveolar, Manner::Plosive, false));
  English.AddPhoneme(std::make_unique<Consonant>(
      L"d", Place::Alveolar, Manner::Plosive, true));
  English.AddPhoneme(
      std::make_unique<Consonant>(L"k", Place::Velar, Manner::Plosive, false));
  English.AddPhoneme(
      std::make_unique<Consonant>(L"ɡ", Place::Velar, Manner::Plosive, true));

  English.AddPhoneme(
      std::make_unique<Consonant>(L"m", Place::Bilabial, Manner::Nasal, true));
  English.AddPhoneme(
      std::make_unique<Consonant>(L"n", Place::Alveolar, Manner::Nasal, true));
  English.AddPhoneme(
      std::make_unique<Consonant>(L"ŋ", Place::Velar, Manner::Nasal, true));

  English.AddPhoneme(std::make_unique<Consonant>(
      L"f", Place::Labiodental, Manner::Fricative, false));
  English.AddPhoneme(std::make_unique<Consonant>(
      L"v", Place::Labiodental, Manner::Fricative, true));
  English.AddPhoneme(std::make_unique<Consonant>(
      L"θ", Place::Dental, Manner::Fricative, false));
  English.AddPhoneme(std::make_unique<Consonant>(
      L"ð", Place::Dental, Manner::Fricative, true));
  English.AddPhoneme(std::make_unique<Consonant>(
      L"s", Place::Alveolar, Manner::Fricative, false));
  English.AddPhoneme(std::make_unique<Consonant>(
      L"z", Place::Alveolar, Manner::Fricative, true));
  English.AddPhoneme(std::make_unique<Consonant>(
      L"ʃ", Place::Postalveolar, Manner::Fricative, false));
  English.AddPhoneme(std::make_unique<Consonant>(
      L"ʒ", Place::Postalveolar, Manner::Fricative, true));
  English.AddPhoneme(std::make_unique<Consonant>(
      L"h", Place::Glottal, Manner::Fricative, false));

  English.AddPhoneme(std::make_unique<Consonant>(
      L"l", Place::Alveolar, Manner::Approximant, true));
  English.AddPhoneme(std::make_unique<Consonant>(
      L"ɹ", Place::Alveolar, Manner::Approximant, true));
  English.AddPhoneme(std::make_unique<Consonant>(
      L"j", Place::Palatal, Manner::Approximant, true));
  English.AddPhoneme(std::make_unique<Consonant>(
      L"w", Place::Bilabial, Manner::Approximant, true));

  English.AddPhoneme(std::make_unique<Consonant>(
      L"ʧ", Place::Postalveolar, Manner::Affricate, false));
  English.AddPhoneme(std::make_unique<Consonant>(
      L"ʤ", Place::Postalveolar, Manner::Affricate, true));
  English.AddPhoneme(std::make_unique<Vowel>(
      L"ɝ", Height::Mid, Backness::Central, false, false));

  English.AddPhoneme(std::make_unique<Vowel>(
      L"i", Height::High, Backness::Front, true, false));
  English.AddPhoneme(std::make_unique<Vowel>(
      L"ɪ", Height::High, Backness::Front, false, false));
  English.AddPhoneme(
      std::make_unique<Vowel>(L"e", Height::Mid, Backness::Front, true, false));
  English.AddPhoneme(std::make_unique<Vowel>(
      L"ɛ", Height::Mid, Backness::Front, false, false));
  English.AddPhoneme(std::make_unique<Vowel>(
      L"æ", Height::Low, Backness::Front, false, false));

  English.AddPhoneme(std::make_unique<Vowel>(
      L"ə", Height::Mid, Backness::Central, false, false));
  English.AddPhoneme(std::make_unique<Vowel>(
      L"ʌ", Height::Mid, Backness::Central, false, false));

  English.AddPhoneme(
      std::make_unique<Vowel>(L"a", Height::Low, Backness::Front, true, false));
  English.AddPhoneme(
      std::make_unique<Vowel>(L"u", Height::High, Backness::Back, true, true));
  English.AddPhoneme(
      std::make_unique<Vowel>(L"ʊ", Height::High, Backness::Back, false, true));
  English.AddPhoneme(
      std::make_unique<Vowel>(L"ɔ", Height::Mid, Backness::Back, false, true));
  English.AddPhoneme(
      std::make_unique<Vowel>(L"o", Height::Mid, Backness::Back, true, true));
  English.AddPhoneme(
      std::make_unique<Vowel>(L"ɑ", Height::Low, Backness::Back, false, false));

  auto nucleus_exists =
      Rule{L"Nucleus must exist",
           RuleType::Nucleus,
           [](const SyllablePart& nucleus) { return !nucleus.empty(); }};

  auto nucleus_only_vowels = Rule{L"Nucleus must contain only vowels",
                                  RuleType::Nucleus,
                                  [](const SyllablePart& nucleus) {
                                    for (const auto& p : nucleus) {
                                      if (p->GetType() != PhonemeType::kVowel)
                                        return false;
                                    }
                                    return true;
                                  }};

  auto onset_only_consonants =
      Rule{L"Onset must contain only consonants",
           RuleType::Onset,
           [](const SyllablePart& onset) {
             for (const auto& p : onset) {
               if (p->GetType() != PhonemeType::kConsonant) return false;
             }
             return true;
           }};

  auto coda_only_consonants =
      Rule{L"Coda must contain only consonants",
           RuleType::Coda,
           [](const SyllablePart& coda) {
             for (const auto& p : coda) {
               if (p->GetType() != PhonemeType::kConsonant) return false;
             }
             return true;
           }};

  auto max_onset_size =
      Rule{L"Onset may have at most 3 consonants",
           RuleType::Onset,
           [](const SyllablePart& onset) { return onset.size() <= 3; }};

  auto max_coda_size =
      Rule{L"Coda may have at most 4 consonants",
           RuleType::Coda,
           [](const SyllablePart& coda) { return coda.size() <= 4; }};

  auto max_nucleus_size =
      Rule{L"Nucleus may have at most 2 vowels",
           RuleType::Nucleus,
           [](const SyllablePart& nucleus) { return nucleus.size() <= 2; }};

  auto three_consonant_onset_rule =
      Rule{L"Three-consonant English onsets must start with s",
           RuleType::Onset,
           [](const SyllablePart& onset) {
             if (onset.size() != 3) return true;
             return onset[0]->GetSymbol() == L"s";
           }};

  auto english_onset_ng_rule = Rule{L"Syllables cannot begin with ng",
                                    RuleType::Onset,
                                    [](const SyllablePart& onset) {
                                      if (onset.empty()) return true;
                                      return onset[0]->GetSymbol() != L"ŋ";
                                    }};

  auto coda_h_rule = Rule{L"Syllables cannot end with h",
                          RuleType::Coda,
                          [](const SyllablePart& coda) {
                            if (coda.empty()) return true;
                            return coda.back()->GetSymbol() != L"h";
                          }};

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

  English.SetTokenConverter(
      [](const std::wstring& token) -> std::optional<Symbol> {
        if (token.empty()) return std::nullopt;

        std::wstring stripped;

        if (static_cast<bool>(std::iswdigit(token.back()))) {
          stripped = token.substr(0, token.size() - 1);
        } else {
          stripped = token;
        }

        std::string key;
        key.reserve(stripped.size());
        for (wchar_t c : stripped) {
          if (c > 0x7F) return std::nullopt;
          key.push_back(static_cast<char>(c));
        }

        Symbol ipa = Lookup(key);
        if (ipa == L"\0") return std::nullopt;
        return ipa;
      });

  return English;
}
// NOLINTEND