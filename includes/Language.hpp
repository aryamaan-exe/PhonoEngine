#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <functional>
#include <memory>
#include <optional>
#include <unordered_map>

#include "Phoneme.hpp"
#include "Rule.hpp"
#include "Word.hpp"

using Inventory = std::vector<std::unique_ptr<Phoneme>>;
using TokenConverter =
    std::function<std::optional<Symbol>(const std::wstring&)>;

struct ValidationResult {
  bool valid;
  std::wstring reason;
};

class Language {
public:
  void AddPhoneme(std::unique_ptr<Phoneme> phoneme);
  void AddRule(Rule* rule);
  void SetTokenConverter(TokenConverter converter);
  ValidationResult Validate(Word word);
  Word BuildWordFromSymbols(std::vector<Symbol>& word);
  Phoneme* GetPhonemeFromSymbol(const Symbol& symbol);
  std::vector<Syllable> GetSyllablesFromTokens(
      const std::vector<std::wstring>& tokens);

private:
  Inventory inventory_;
  std::unordered_map<Symbol, Phoneme*> symbols_;
  std::vector<Rule*> rules_;
  TokenConverter converter_;
};

#endif