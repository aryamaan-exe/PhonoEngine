#ifndef VOWEL_HPP
#define VOWEL_HPP

#include <string>

#include "Phoneme.hpp"

enum class Height { High, Mid, Low };
enum class Backness { Front, Central, Back };

class Vowel : public Phoneme {
public:
  Vowel(std::string symbol,
        Height height,
        Backness backness,
        bool tenseness,
        bool roundedness);
  Height GetHeight();
  Backness GetBackness();
  bool GetTenseness() const;
  bool GetRoundedness() const;

private:
  Height height_;
  Backness backness_;
  bool tense_;
  bool rounded_;
};

#endif