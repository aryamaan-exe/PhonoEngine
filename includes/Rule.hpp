#ifndef RULE_HPP
#define RULE_HPP

#include <functional>
#include <string>

#include "Phoneme.hpp"

class Rule {
public:
  Rule(std::string& name,
       std::function<bool(std::vector<Phoneme*>&)>& condition);

private:
  std::string name_;
  std::function<bool(std::vector<Phoneme*>&)> condition_;
};

#endif