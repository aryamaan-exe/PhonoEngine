#include "Rule.hpp"

Rule::Rule(const std::string& name,
           RuleType type,
           const std::function<bool(const std::vector<Phoneme*>&)>& condition):
    name_(name), type_(type), condition_(condition) {}

bool Rule::IsValid(const std::vector<Phoneme*>& syllable_part) {
  return condition_(syllable_part);
}

RuleType Rule::GetType() { return type_; }

std::string Rule::GetName() { return name_; }