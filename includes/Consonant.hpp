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

enum class Manner { Plosive, Nasal, Trill, Tap, Fricative, Approximant };

class Consonant : public Phoneme {
public:
  Consonant(std::string symbol, Place place, Manner manner, bool voiced);
  Place GetPlace();
  Manner GetManner();
  bool Voiced();

private:
  Place place_;
  Manner manner_;
  bool voiced_;
};

#endif