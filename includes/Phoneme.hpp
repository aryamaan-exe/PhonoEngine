#ifndef PHONEME_HPP
#define PHONEME_HPP

#include <string>

using Symbol = std::wstring;

enum class PhonemeType { kConsonant, kVowel };

class Phoneme {
public:
  Phoneme(Symbol symbol, PhonemeType type);
  virtual ~Phoneme() = default;
  
  Symbol GetSymbol() const;
  PhonemeType GetType() const;

private:
  Symbol symbol_;
  PhonemeType type_;
};

#endif