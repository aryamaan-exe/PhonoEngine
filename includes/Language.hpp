#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <unordered_map>  
#include "Phoneme.hpp"
#include "Rule.hpp"
#include "Word.hpp"

using Inventory = std::vector<std::unique_ptr<Phoneme>>;

struct ValidationResult {
  bool valid;
  std::wstring reason;
};

class Language {
public:
  void AddPhoneme(std::unique_ptr<Phoneme> phoneme);
  void AddRule(Rule* rule);
  ValidationResult Validate(Word word);
  Word BuildWordFromSymbols(std::vector<Symbol>& word);
  Phoneme* GetPhonemeFromSymbol(Symbol symbol);
  std::vector<Syllable> GetSyllablesFromTokens(const std::vector<std::wstring>& tokens);
private:
  Inventory inventory_;
  std::unordered_map<Symbol, Phoneme*> symbols_;
  std::vector<Rule*> rules_;
};

#endif