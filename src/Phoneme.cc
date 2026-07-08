#include "Phoneme.hpp"

Phoneme::Phoneme(wchar_t symbol, PhonemeType type):
    symbol_(symbol), type_(type) {}

wchar_t Phoneme::GetSymbol() const { return symbol_; }

PhonemeType Phoneme::GetType() const { return type_; }