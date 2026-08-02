#ifndef CONSONANT_HPP
#define CONSONANT_HPP

#include <string>

#include "Phoneme.hpp"

// NOLINTBEGIN(readability-identifier-naming)
enum class Place {
  Bilabial,
  Labiodental,
  Dental,
  Alveolar,
  Postalveolar,
  Retroflex,
  Palatal,
  Velar,
  Uvular,
  Pharyngeal,
  Glottal
};

enum class Manner {
  Plosive,
  Nasal,
  Trill,
  Tap,
  Fricative,
  LateralFricative,
  Approximant,
  LateralApproximant,
  Affricate
};
// NOLINTEND(readability-identifier-naming)

class Consonant : public Phoneme {
public:
  Consonant(const Consonant& other) = default;
  Consonant(Consonant&&) = default;
  Consonant& operator=(const Consonant& other) = default;
  Consonant& operator=(Consonant&&) = default;
  ~Consonant() override = default;

  Consonant(Symbol symbol, Place place, Manner manner, bool voiced);
  std::unique_ptr<Phoneme> Clone() const override;
  Place GetPlace() const;
  Manner GetManner() const;
  bool Voiced() const;

private:
  Place place_;
  Manner manner_;
  bool voiced_;
};

#endif