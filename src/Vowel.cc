#include "Vowel.hpp"

Vowel::Vowel(std::string symbol,
             Height height,
             Backness backness,
             bool tenseness,
             bool roundedness):
    symbol_(std::move(symbol)),
    height_(height),
    backness_(backness),
    tense_(tenseness),
    rounded_(roundedness) {}