#include "Syllable.hpp"

class Word {
public:
    Word(const std::vector<Syllable>& syllables);
    std::string Symbols();
private:
    std::vector<Syllable> syllables_;
};