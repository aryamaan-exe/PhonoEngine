#include "Phoneme.hpp"

Phoneme::Phoneme(std::string symbol, PhonemeType type):
    symbol_(symbol), type_(type) {}

std::string Phoneme::GetSymbol() { return symbol_; }

PhonemeType Phoneme::GetType() { return type_; }