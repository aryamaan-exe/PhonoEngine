#ifndef CONSONANT_HPP
#define CONSONANT_HPP

#include <string>

#include "Phoneme.hpp"

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
  Approximant,
  Affricate
};

class Consonant : public Phoneme {
public:
  Consonant(Symbol symbol, Place place, Manner manner, bool voiced);
  Place GetPlace() const;
  Manner GetManner() const;
  bool Voiced() const;

private:
  Place place_;
  Manner manner_;
  bool voiced_;
};

#endif