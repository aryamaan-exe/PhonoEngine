#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include <map>

#include "Consonant.hpp"
#include "Language.hpp"
#include "Rule.hpp"
#include "Syllable.hpp"
#include "Vowel.hpp"
#include "Word.hpp"

constexpr std::array<std::pair<std::string_view, Symbol>, 39> kPhoneticMap{{
    {"AA", L"\u0251"},  // ɑ
    {"AE", L"\u00E6"},  // æ
    {"AH", L"\u028C"},  // ʌ
    {"AO", L"\u0254"},  // ɔ
    {"AW", L"\u0061"},  // a
    {"AY", L"\u0061"},  // a
    {"EH", L"\u025B"},  // ɛ
    {"ER", L"\u025D"},  // ɝ
    {"EY", L"\u0065"},  // e
    {"IH", L"\u026A"},  // ɪ
    {"IY", L"\u0069"},  // i
    {"OW", L"\u006F"},  // o
    {"OY", L"\u0254"},  // ɔ
    {"UH", L"\u028A"},  // ʊ
    {"UW", L"\u0075"},  // u

    {"B", L"\u0062"},   // b
    {"CH", L"\u02A7"},  // ʧ
    {"D", L"\u0064"},   // d
    {"DH", L"\u00F0"},  // ð
    {"F", L"\u0066"},   // f
    {"G", L"\u0261"},   // ɡ
    {"HH", L"\u0068"},  // h
    {"JH", L"\u02A4"},  // ʤ
    {"K", L"\u006B"},   // k
    {"L", L"\u006C"},   // l
    {"M", L"\u006D"},   // m
    {"N", L"\u006E"},   // n
    {"NG", L"\u014B"},  // ŋ
    {"P", L"\u0070"},   // p
    {"R", L"\u0279"},   // ɹ
    {"S", L"\u0073"},   // s
    {"SH", L"\u0283"},  // ʃ
    {"T", L"\u0074"},   // t
    {"TH", L"\u03B8"},  // θ
    {"V", L"\u0076"},   // v
    {"W", L"\u0077"},   // w
    {"Y", L"\u006A"},   // j
    {"Z", L"\u007A"},   // z
    {"ZH", L"\u0292"},  // ʒ
}};

constexpr Symbol Lookup(std::string_view key) {
  auto it = std::find_if(kPhoneticMap.begin(),
                         kPhoneticMap.end(),
                         [&](auto& p) { return p.first == key; });
  return it != kPhoneticMap.end() ? it->second : L"\0";
}

std::vector<std::wstring> Split(const std::wstring& s) {
  std::wistringstream iss{s};
  std::vector<std::wstring> tokens;
  std::wstring token;
  while (iss >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

int main() {
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
      std::make_unique<Consonant>(L"g", Place::Velar, Manner::Plosive, true));

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
      std::make_unique<Vowel>(L"u", Height::High, Backness::Back, true, true));
  English.AddPhoneme(
      std::make_unique<Vowel>(L"ʊ", Height::High, Backness::Back, false, true));
  English.AddPhoneme(
      std::make_unique<Vowel>(L"ɔ", Height::Mid, Backness::Back, false, true));
  English.AddPhoneme(
      std::make_unique<Vowel>(L"ɑ", Height::Low, Backness::Back, false, false));

  auto* nucleus_exists =
      new Rule(L"Nucleus must exist",
               RuleType::Nucleus,
               [](const SyllablePart& nucleus) { return !nucleus.empty(); });

  auto* nucleus_only_vowels =
      new Rule(L"Nucleus must contain only vowels",
               RuleType::Nucleus,
               [](const SyllablePart& nucleus) {
                 for (const auto& p : nucleus) {
                   if (p->GetType() != PhonemeType::kVowel) return false;
                 }
                 return true;
               });

  auto* onset_only_consonants =
      new Rule(L"Onset must contain only consonants",
               RuleType::Onset,
               [](const SyllablePart& onset) {
                 for (const auto& p : onset) {
                   if (p->GetType() != PhonemeType::kConsonant) return false;
                 }
                 return true;
               });

  auto* coda_only_consonants =
      new Rule(L"Coda must contain only consonants",
               RuleType::Coda,
               [](const SyllablePart& coda) {
                 for (const auto& p : coda) {
                   if (p->GetType() != PhonemeType::kConsonant) return false;
                 }
                 return true;
               });

  auto* max_onset_size =
      new Rule(L"Onset may have at most 3 consonants",
               RuleType::Onset,
               [](const SyllablePart& onset) { return onset.size() <= 3; });

  auto* max_coda_size =
      new Rule(L"Coda may have at most 4 consonants",
               RuleType::Coda,
               [](const SyllablePart& coda) { return coda.size() <= 4; });

  auto* max_nucleus_size =
      new Rule(L"Nucleus may have at most 2 vowels",
               RuleType::Nucleus,
               [](const SyllablePart& nucleus) { return nucleus.size() <= 2; });

  auto* three_consonant_onset_rule =
      new Rule(L"Three-consonant English onsets must start with s",
               RuleType::Onset,
               [](const SyllablePart& onset) {
                 if (onset.size() != 3) return true;
                 return onset[0]->GetSymbol() == L"s";
               });

  auto* english_onset_ng_rule = new Rule(L"Syllables cannot begin with ng",
                                         RuleType::Onset,
                                         [](const SyllablePart& onset) {
                                           if (onset.empty()) return true;
                                           return onset[0]->GetSymbol() != L"ŋ";
                                         });

  auto* coda_h_rule = new Rule(L"Syllables cannot end with h",
                               RuleType::Coda,
                               [](const SyllablePart& coda) {
                                 if (coda.empty()) return true;
                                 return coda.back()->GetSymbol() != L"h";
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

  std::wifstream dict{"cmudict.dict"};

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

  if (!dict) throw std::runtime_error("Could not open file");

  std::vector<std::wstring> lines;
  std::wstring line;
  while (std::getline(dict, line)) {
    lines.push_back(std::move(line));
  }

  const size_t kThreadCount{std::thread::hardware_concurrency()};
  std::vector<std::jthread> threads;
  const size_t kChunkSize{(lines.size() + kThreadCount - 1) / kThreadCount};
  std::vector<std::wstring> invalid;

  std::map<std::wstring, Word> dictionary;

  for (size_t t{}; t < kThreadCount; ++t) {
    size_t begin{t * kChunkSize};
    size_t end{std::min(begin + kChunkSize, lines.size())};

    if (begin >= end) continue;

    threads.emplace_back([&, begin, end] {
      for (size_t j{begin}; j < end; ++j) {
        const std::vector<std::wstring> tokens{Split(lines.at(j))};
        std::vector<Syllable> syllables{English.GetSyllablesFromTokens(tokens)};
        Word word{syllables};
        const std::wstring& spelling = tokens.at(0);
        dictionary[spelling] = word;
      }
    });
  }
}
