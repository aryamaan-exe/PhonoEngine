#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

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

std::vector<std::string> Split(const std::string& s) {
  std::istringstream iss{s};
  std::vector<std::string> tokens;
  std::string token;
  while (iss >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

int main() {
  Language English;

  English.AddPhoneme(
      new Consonant(L"p", Place::Bilabial, Manner::Plosive, false));
  English.AddPhoneme(
      new Consonant(L"b", Place::Bilabial, Manner::Plosive, true));
  English.AddPhoneme(
      new Consonant(L"t", Place::Alveolar, Manner::Plosive, false));
  English.AddPhoneme(
      new Consonant(L"d", Place::Alveolar, Manner::Plosive, true));
  English.AddPhoneme(new Consonant(L"k", Place::Velar, Manner::Plosive, false));
  English.AddPhoneme(new Consonant(L"g", Place::Velar, Manner::Plosive, true));

  English.AddPhoneme(new Consonant(L"m", Place::Bilabial, Manner::Nasal, true));
  English.AddPhoneme(new Consonant(L"n", Place::Alveolar, Manner::Nasal, true));
  English.AddPhoneme(new Consonant(L"ŋ", Place::Velar, Manner::Nasal, true));

  English.AddPhoneme(
      new Consonant(L"f", Place::Labiodental, Manner::Fricative, false));
  English.AddPhoneme(
      new Consonant(L"v", Place::Labiodental, Manner::Fricative, true));
  English.AddPhoneme(
      new Consonant(L"θ", Place::Dental, Manner::Fricative, false));
  English.AddPhoneme(
      new Consonant(L"ð", Place::Dental, Manner::Fricative, true));
  English.AddPhoneme(
      new Consonant(L"s", Place::Alveolar, Manner::Fricative, false));
  English.AddPhoneme(
      new Consonant(L"z", Place::Alveolar, Manner::Fricative, true));
  English.AddPhoneme(
      new Consonant(L"ʃ", Place::Postalveolar, Manner::Fricative, false));
  English.AddPhoneme(
      new Consonant(L"ʒ", Place::Postalveolar, Manner::Fricative, true));
  English.AddPhoneme(
      new Consonant(L"h", Place::Glottal, Manner::Fricative, false));

  English.AddPhoneme(
      new Consonant(L"l", Place::Alveolar, Manner::Approximant, true));
  English.AddPhoneme(
      new Consonant(L"ɹ", Place::Alveolar, Manner::Approximant, true));
  English.AddPhoneme(
      new Consonant(L"j", Place::Palatal, Manner::Approximant, true));
  English.AddPhoneme(
      new Consonant(L"w", Place::Bilabial, Manner::Approximant, true));

  English.AddPhoneme(
      new Consonant(L"ʧ", Place::Postalveolar, Manner::Affricate, false));
  English.AddPhoneme(
      new Consonant(L"ʤ", Place::Postalveolar, Manner::Affricate, true));
  English.AddPhoneme(
      new Vowel(L"ɝ", Height::Mid, Backness::Central, false, false));

  English.AddPhoneme(
      new Vowel(L"i", Height::High, Backness::Front, true, false));
  English.AddPhoneme(
      new Vowel(L"ɪ", Height::High, Backness::Front, false, false));
  English.AddPhoneme(
      new Vowel(L"e", Height::Mid, Backness::Front, true, false));
  English.AddPhoneme(
      new Vowel(L"ɛ", Height::Mid, Backness::Front, false, false));
  English.AddPhoneme(
      new Vowel(L"æ", Height::Low, Backness::Front, false, false));

  English.AddPhoneme(
      new Vowel(L"ə", Height::Mid, Backness::Central, false, false));
  English.AddPhoneme(
      new Vowel(L"ʌ", Height::Mid, Backness::Central, false, false));

  English.AddPhoneme(new Vowel(L"u", Height::High, Backness::Back, true, true));
  English.AddPhoneme(
      new Vowel(L"ʊ", Height::High, Backness::Back, false, true));
  English.AddPhoneme(new Vowel(L"ɔ", Height::Mid, Backness::Back, false, true));
  English.AddPhoneme(
      new Vowel(L"ɑ", Height::Low, Backness::Back, false, false));

  auto* nucleus_exists = new Rule(
      L"Nucleus must exist",
      RuleType::Nucleus,
      [](const std::vector<Phoneme*>& nucleus) { return !nucleus.empty(); });

  auto* nucleus_only_vowels =
      new Rule(L"Nucleus must contain only vowels",
               RuleType::Nucleus,
               [](const std::vector<Phoneme*>& nucleus) {
                 for (Phoneme* p : nucleus) {
                   if (p->GetType() != PhonemeType::kVowel) return false;
                 }
                 return true;
               });

  auto* onset_only_consonants =
      new Rule(L"Onset must contain only consonants",
               RuleType::Onset,
               [](const std::vector<Phoneme*>& onset) {
                 for (Phoneme* p : onset) {
                   if (p->GetType() != PhonemeType::kConsonant) return false;
                 }
                 return true;
               });

  auto* coda_only_consonants =
      new Rule(L"Coda must contain only consonants",
               RuleType::Coda,
               [](const std::vector<Phoneme*>& coda) {
                 for (Phoneme* p : coda) {
                   if (p->GetType() != PhonemeType::kConsonant) return false;
                 }
                 return true;
               });

  auto* max_onset_size = new Rule(
      L"Onset may have at most 3 consonants",
      RuleType::Onset,
      [](const std::vector<Phoneme*>& onset) { return onset.size() <= 3; });

  auto* max_coda_size = new Rule(
      L"Coda may have at most 4 consonants",
      RuleType::Coda,
      [](const std::vector<Phoneme*>& coda) { return coda.size() <= 4; });

  auto* max_nucleus_size = new Rule(
      L"Nucleus may have at most 2 vowels",
      RuleType::Nucleus,
      [](const std::vector<Phoneme*>& nucleus) { return nucleus.size() <= 2; });

  auto* three_consonant_onset_rule =
      new Rule(L"Three-consonant English onsets must start with s",
               RuleType::Onset,
               [](const std::vector<Phoneme*>& onset) {
                 if (onset.size() != 3) return true;
                 return onset[0]->GetSymbol() == L"s";
               });

  auto* english_onset_ng_rule =
      new Rule(L"Syllables cannot begin with ng",
               RuleType::Onset,
               [](const std::vector<Phoneme*>& onset) {
                 if (onset.empty()) return true;
                 return onset[0]->GetSymbol() != L"ŋ";
               });

  auto* coda_h_rule = new Rule(L"Syllables cannot end with h",
                               RuleType::Coda,
                               [](const std::vector<Phoneme*>& coda) {
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

  std::ifstream dict{"cmudict.dict"};
  if (!dict) throw std::runtime_error("Could not open file");

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(dict, line)) {
    lines.push_back(std::move(line));
  }

  const size_t kThreadCount{std::thread::hardware_concurrency()};
  std::vector<std::thread> threads;
  std::vector<bool> result;
  size_t valid{};
  const size_t kChunkSize{(lines.size() + kThreadCount - 1) / kThreadCount};

  for (size_t t{}; t < kThreadCount; ++t) {
    size_t begin{t * kChunkSize};
    size_t end{std::min(begin + kChunkSize, lines.size())};

    if (begin >= end) continue;

    threads.emplace_back([&, begin, end] {
      for (size_t j{begin}; j < end; ++j) {
        std::vector<std::string> tokens = Split(lines.at(j));
        std::vector<Syllable> syllables = Syllable::GetSyllablesFromTokens(tokens);
        Word w{tokens.at(0), syllables};
        bool is_valid = English.Validate(w);
        if (is_valid) ++valid;
        result.push_back(is_valid);
      }
    });
  }

  for (auto& thread : threads) thread.join();

	std::cout << valid / lines.size();
}
