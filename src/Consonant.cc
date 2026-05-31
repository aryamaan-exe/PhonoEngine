#include "Consonant.hpp"

Consonant::Consonant(std::string symbol,
                     Place place,
                     Manner manner,
                     bool voicing):
    symbol_(std::move(symbol)),
    place_(place),
    manner_(manner),
    voiced_(voicing) {}