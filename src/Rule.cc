#include "Rule.hpp"

Rule::Rule(const std::wstring& name,
           RuleType type,
           const std::function<bool(const SyllablePart&)>& condition):
    name_(name), type_(type), condition_(condition) {}

bool Rule::IsValid(const SyllablePart& syllable_part) const {
  return condition_(syllable_part);
}

RuleType Rule::GetType() const { return type_; }

std::wstring Rule::GetName() const { return name_; }