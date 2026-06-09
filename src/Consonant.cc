#include "Consonant.hpp"

#include "Phoneme.hpp"

Consonant::Consonant(std::string symbol,
                     Place place,
                     Manner manner,
                     bool voicing):
    Phoneme(symbol, PhonemeType::kConsonant),
    place_(place),
    manner_(manner),
    voiced_(voicing) {}

Place Consonant::GetPlace() { return place_; }

Manner Consonant::GetManner() { return manner_; }

bool Consonant::Voiced() { return voiced_; }