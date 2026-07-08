#include "Vowel.hpp"

#include "Phoneme.hpp"

Vowel::Vowel(wchar_t symbol,
             Height height,
             Backness backness,
             bool tenseness,
             bool roundedness):
    Phoneme(symbol, PhonemeType::kVowel),
    height_(height),
    backness_(backness),
    tense_(tenseness),
    rounded_(roundedness) {}

Height Vowel::GetHeight() const { return height_; }

Backness Vowel::GetBackness() const { return backness_; }

bool Vowel::GetTenseness() const { return tense_; }

bool Vowel::GetRoundedness() const { return rounded_; }
