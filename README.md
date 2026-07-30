# PhonoEngine

PhonoEngine is a phonological rule engine which describes constructs from phonemes all the way to languages. You can define all phonemes in your language and nucleus, onset, and coda rules. From there, you can validate words using the rule engine, generate new words using the rules, track sound changes, and so much more.

The example in `driver.cc` is a concurrent version of the rule validation engine running on the Carnegie Mellon Pronouncing Dictionary. Other examples and test cases are in progress.

C++ development environment cloned from [here](https://github.com/cs128-illinois/env-dotfiles).

## Classes

### Phoneme

Abstract sound unit. Inherited by Consonant and Vowel.

**Functions:**

(`Symbol = std::wstring`)

1) `Symbol GetSymbol()`: IPA symbol of phoneme for predefined phonemes. Can be defined with orthography for custom phonemes.
2) `PhonemeType GetType()`: Enum PhonemeType of either kConsonant or kVowel.

**Enums:**

`PhonemeType`: kConsonant, kVowel

### Consonant

**Functions:**

1) `Consonant(Symbol symbol, Place place, Manner manner, bool voiced)`: Constructor with place and manner enums.
2) `Place GetPlace()`: Enum for place of articulation. 
3) `Manner GetManner()`: Enum for manner of articulation. 
4) `bool GetVoicing()`: True for voiced consonants.

**Enums:**

`Place`: One of Bilabial, Labiodental, Dental, Alveolar, Postalveolar, Retroflex, Palatal, Velar, Uvular, Pharyngeal, Glottal.

`Manner`: One of Plosive, Nasal, Trill, Tap, Fricative, Approximant.

### Vowel

**Functions:**

1) `Vowel(Symbol symbol, Height height, Backness backness, bool tenseness, bool roundedness)`: Constructor. Takes in height and backness enums.
2) `Height GetHeight()`: Enum for height of vowel. 
3) `Backness GetBackness()`: Enum for backness of vowel.
4) `bool GetTenseness()`: True for tense vowels.
5) `bool GetRoundedness()`: True for rounded vowels.

**Enums:**

`Height`: One of High, Mid, Low.

`Backness`: One of Front, Central, Back.

### Syllable

**Functions:**

(`SyllablePart = std::vector<Phoneme*>`)

1) `Syllable(SyllablePart& onset, SyllablePart& nucleus, SyllablePart& coda)`: Constructor. Initializes the onset, nucleus, and coda as a `std::vector` of pointers to phonemes.

2) `SyllablePart GetOnset()`: Returns the onset.

3) `SyllablePart GetNucleus()`: Returns the nucleus.

4) `SyllablePart GetCoda()`: Returns the coda.

5) `Symbol Symbols()`: String of characters (as defined by the consonant or vowel's constructor which is obtained from `Phoneme`'s `GetSymbol()` method) that make up the entire syllable.

### Word

**Functions:**

1) `Word(const std::vector<Syllable>& syllables)`: Create a Word object from a vector of syllables.

2) `std::vector<Syllable> GetSyllables()`: Retrieve a vector of syllables that make up the word.

3) `Symbol Symbols()`: Get the IPA/custom representation of the word.

### Rule

**Functions:**

1) `Rule(const std::wstring& name, RuleType type, const std::function<bool(const SyllablePart&)>& condition)`: Creates a Rule object with a name, rule type and a validation function stored as a `std::function`. This validation function returns a `bool` and expects a `SyllablePart` to validate on.

2) `bool IsValid(const SyllablePart& syllable_part)`: This runs the validation function on a syllable part.

2) `RuleType GetType()`: This returns the rule type as an enum.

3) `std::wstring GetName()`: This returns the name of the rule.

**Enums:**

`RuleType`: One of Onset, Nucleus, Coda.

### Language

Used for defining a language's phonemic inventory and phonological rules.

(`TokenConverter = std::function<std::optional<Symbol>(const std::wstring&)>`)

A `TokenConverter` function should return `std::nullopt` for nonexistent tokens or a `Symbol` for the corresponding symbol. This can be used for Romaji, ARPABet (as shown in `driver.cc`) or any other system where an input dataset might not correspond with IPA or another desired writing system.

1) `void AddPhoneme(std::unique_ptr<Phoneme> phoneme)`: Adds a phoneme to phonemic inventory.

2) `void AddRule(Rule* rule)`: Adds a rule to the phonological ruleset.

3) `void SetTokenConverter(TokenConverter converter)`: Takes in a 

4) `ValidationResult Validate(Word word)`: Returns a `ValidationResult` struct, which has member variables `bool valid` and `std::wstring reason`. Reason is either the rule name which fails, or empty if valid.

5) `Word BuildWordFromSymbols(std::vector<Symbol>& word)`: Returns a `Word` object constructed from phonemes from the language's phonemic inventory. These phonemes are constructed by matching the symbol defined for the phoneme.

6) `Phoneme* GetPhonemeFromSymbol(Symbol symbol)`: Returns a phoneme pointer for any symbol according to the phonemic inventory.

7) `std::vector<Syllable> GetSyllablesFromTokens(const std::vector<std::wstring>& tokens)`: Returns a syllable construction from given tokens.
