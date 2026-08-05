#ifndef PHONEME_HPP
#define PHONEME_HPP

#include <string>
#include <memory>

using Symbol = std::wstring;

enum class PhonemeType { kConsonant, kVowel };

class Phoneme {
public:
  Phoneme(const Phoneme& other) = default;
  Phoneme(Phoneme&&) = default;
  Phoneme& operator=(const Phoneme& other) = default;
  Phoneme& operator=(Phoneme&&) = default;
  virtual ~Phoneme() = default;

  Phoneme(const Symbol& symbol, PhonemeType type);
  virtual std::unique_ptr<Phoneme> Clone() const = 0;
  
  Symbol GetSymbol() const;
  PhonemeType GetType() const;

private:
  Symbol symbol_;
  PhonemeType type_;
};

#endif