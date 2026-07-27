#ifndef RULE_HPP
#define RULE_HPP

#include <functional>
#include <string>

#include "Phoneme.hpp"
#include "Syllable.hpp"

enum class RuleType { Onset, Nucleus, Coda };

class Rule {
public:
  Rule(const std::wstring& name,
       RuleType type,
       const std::function<bool(const SyllablePart&)>& condition);

  bool IsValid(const SyllablePart& syllable_part) const;

  RuleType GetType() const;

  std::wstring GetName() const;

private:
  std::wstring name_;
  RuleType type_;
  std::function<bool(const SyllablePart&)> condition_;
};

#endif