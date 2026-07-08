#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <unordered_map>  
#include "Phoneme.hpp"
#include "Rule.hpp"
#include "Word.hpp"

class Language {
public:
  void AddPhoneme(Phoneme* phoneme);
  void AddRule(const Rule* rule);
  bool Validate(Word word);
  Word BuildWordFromSymbols(std::vector<wchar_t>& word);
  Phoneme GetPhonemeFromSymbol(wchar_t symbol);

private:
  std::vector<Phoneme> inventory_;
  std::unordered_map<wchar_t, Phoneme> symbols_;
  std::vector<Rule> rules_;
};

#endif