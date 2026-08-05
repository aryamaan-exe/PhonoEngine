#include "Phoneme.hpp"

Phoneme::Phoneme(const Symbol& symbol, PhonemeType type):
    symbol_(symbol), type_(type) {}

Symbol Phoneme::GetSymbol() const { return symbol_; }

PhonemeType Phoneme::GetType() const { return type_; }