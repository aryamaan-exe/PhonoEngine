#ifndef VOWEL_HPP
#define VOWEL_HPP

#include <string>

#include "Phoneme.hpp"

enum class Height { High, Mid, Low };
enum class Backness { Front, Central, Back };

class Vowel : public Phoneme {
public:
  Vowel(wchar_t symbol,
        Height height,
        Backness backness,
        bool tenseness,
        bool roundedness);
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