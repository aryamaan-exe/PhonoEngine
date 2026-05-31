#ifndef PHONEME_HPP
#define PHONEME_HPP

#include <string>

class Phoneme {
public:
  std::string GetSymbol();

private:
  std::string symbol_;
};

#endif