#ifndef PHONEME_HPP
#define PHONEME_HPP

#include <string>

enum class PhonemeType { kConsonant, kVowel };

class Phoneme {
public:
  Phoneme(wchar_t symbol, PhonemeType type);
  wchar_t GetSymbol() const;
  PhonemeType GetType() const;

private:
  wchar_t symbol_;
  PhonemeType type_;
};

#endif