#include "Consonant.hpp"

#include "Phoneme.hpp"

Consonant::Consonant(Symbol symbol, Place place, Manner manner, bool voicing):
    Phoneme(std::move(symbol), PhonemeType::kConsonant),
    place_(place),
    manner_(manner),
    voiced_(voicing) {}

std::unique_ptr<Phoneme> Consonant::Clone() const {
  return std::make_unique<Consonant>(*this);
}

Place Consonant::GetPlace() const { return place_; }

Manner Consonant::GetManner() const { return manner_; }

bool Consonant::Voiced() const { return voiced_; }