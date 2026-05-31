# PhonoEngine

Language phonology validator and rule engine.

C++ development environment cloned from [here](https://github.com/cs128-illinois/env-dotfiles).

## Classes

### Phoneme

Abstract sound unit. Inherited by Consonant and Vowel.

**Functions:**

1) `std::string GetSymbol()`: IPA symbol of phoneme for predefined phonemes. Can be defined with orthography for custom phonemes.

### Consonant

**Functions:**

1) `Consonant(std::string symbol, Place place, Manner manner, bool voiced)`: Constructor with place and manner enums.
2) `Place GetPlace()`: Place of articulation. One of Bilabial, Labiodental, Dental, Alveolar, Postalveolar, Retroflex, Palatal, Velar, Uvular, Pharyngeal, Glottal.
3) `Manner GetManner()`: Manner of articulation. One of Plosive, Nasal, Trill, Tap, Fricative, Approximant.
4) `bool GetVoicing()`: True for voiced consonants.

### Vowel

**Functions:**

1) `Vowel(std::string symbol, Height height, Backness backness, bool tenseness, bool roundedness)`: Constructor. Takes in height and backness enums.
2) `Height GetHeight()`: Height of vowel. One of High, Mid, Low.
3) `Backness GetBackness()`: Backness of vowel. One of Front, Central, Back.
4) `bool GetTenseness()`: True for tense vowels.
5) `bool GetRoundedness()`: True for rounded vowels.