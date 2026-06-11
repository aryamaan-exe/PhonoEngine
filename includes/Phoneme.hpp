#ifndef PHONEME_HPP
#define PHONEME_HPP

#include <string>

enum class PhonemeType { kConsonant, kVowel };

class Phoneme {
public:
  Phoneme(std::string symbol, PhonemeType type);
  std::string GetSymbol();
  PhonemeType GetType();

private:
  std::string symbol_;
  PhonemeType type_;
};

#endif