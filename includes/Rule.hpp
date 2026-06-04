#ifndef RULE_HPP
#define RULE_HPP

#include <functional>
#include <string>

#include "Phoneme.hpp"

class Rule {
public:
  Rule(const std::string& name,
       const std::function<bool(const std::vector<Phoneme*>&)>& condition);

  bool IsValid(const std::vector<Phoneme*>& syllable_part);

private:
  std::string name_;
  std::function<bool(const std::vector<Phoneme*>&)> condition_;
};

#endif