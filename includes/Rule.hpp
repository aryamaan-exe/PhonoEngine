#ifndef RULE_HPP
#define RULE_HPP

#include <functional>
#include <string>

#include "Phoneme.hpp"

enum RuleType { Onset, Nucleus, Coda };

class Rule {
public:
  Rule(const std::string& name,
       RuleType type,
       const std::function<bool(const std::vector<Phoneme*>&)>& condition);

  bool IsValid(const std::vector<Phoneme*>& syllable_part);

  RuleType GetType();

  std::string GetName();

private:
  std::string name_;
  RuleType type_;
  std::function<bool(const std::vector<Phoneme*>&)> condition_;
};

#endif