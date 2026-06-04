# PhonoEngine

Language phonology validator and rule engine.

C++ development environment cloned from [here](https://github.com/cs128-illinois/env-dotfiles).

The file `src/driver.cc` contains some example code for using the classes described below.

## Classes

### Phoneme

Abstract sound unit. Inherited by Consonant and Vowel.

**Functions:**

1) `std::string GetSymbol()`: IPA symbol of phoneme for predefined phonemes. Can be defined with orthography for custom phonemes.
2) `PhonemeType GetType()`: Enum PhonemeType of either kConsonant or kVowel.

**Enums:**

`PhonemeType`: kConsonant, kVowel

### Consonant

**Functions:**

1) `Consonant(std::string symbol, Place place, Manner manner, bool voiced)`: Constructor with place and manner enums.
2) `Place GetPlace()`: Enum for place of articulation. 
3) `Manner GetManner()`: Enum for manner of articulation. 
4) `bool GetVoicing()`: True for voiced consonants.

**Enums:**

`Place`: One of Bilabial, Labiodental, Dental, Alveolar, Postalveolar, Retroflex, Palatal, Velar, Uvular, Pharyngeal, Glottal.

`Manner`: One of Plosive, Nasal, Trill, Tap, Fricative, Approximant.

### Vowel

**Functions:**

1) `Vowel(std::string symbol, Height height, Backness backness, bool tenseness, bool roundedness)`: Constructor. Takes in height and backness enums.
2) `Height GetHeight()`: Enum for height of vowel. 
3) `Backness GetBackness()`: Enum for backness of vowel.
4) `bool GetTenseness()`: True for tense vowels.
5) `bool GetRoundedness()`: True for rounded vowels.

**Enums:**

1) `Height`: One of High, Mid, Low.

2) `Backness`: One of Front, Central, Back.

### Syllable

**Functions:**

1) `Syllable(std::vector<Phoneme*>& onset, std::vector<Phoneme*>& nucleus, std::vector<Phoneme*>& coda)`: Constructor. Initializes the onset, nucleus, and coda as a `std::vector` of pointers to phonemes.

2) `std::vector<Phoneme*> GetOnset()`: Returns the onset.

3) `std::vector<Phoneme*> GetNucleus()`: Returns the nucleus.

4) `std::vector<Phoneme*> GetCoda()`: Returns the coda.

5) `std::string Symbols()`: String of characters (as defined by the consonant or vowel's constructor which is obtained from `Phoneme`'s `GetSymbol()` method) that make up the entire syllable.