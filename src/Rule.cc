#include "Rule.hpp"

Rule::Rule(const std::string& name,
           const std::function<bool(const std::vector<Phoneme*>&)>& condition):
    name_(name), condition_(condition) {}

bool Rule::IsValid(const std::vector<Phoneme*>& syllable_part) {
  return condition_(syllable_part);
}