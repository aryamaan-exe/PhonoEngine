#ifndef VOWEL_HPP
#define VOWEL_HPP

#include <string>

#include "Phoneme.hpp"

// NOLINTBEGIN(readability-identifier-naming)
enum class Height { High, Mid, Low };
enum class Backness { Front, Central, Back };
// NOLINTEND(readability-identifier-naming)

class Vowel : public Phoneme {
public:
  Vowel(const Vowel& other) = default;
  Vowel(Vowel&&) = default;
  Vowel& operator=(const Vowel& other) = default;
  Vowel& operator=(Vowel&&) = default;
  ~Vowel() override = default;

  Vowel(Symbol symbol,
        Height height,
        Backness backness,
        bool tenseness,
        bool roundedness);
  std::unique_ptr<Phoneme> Clone() const override;
  Height GetHeight() const;
  Backness GetBackness() const;
  bool GetTenseness() const;
  bool GetRoundedness() const;

private:
  Height height_;
  Backness backness_;
  bool tense_;
  bool rounded_;
};

#endif