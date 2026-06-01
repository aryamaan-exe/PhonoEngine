#include "Rule.hpp"

Rule::Rule(std::string& name,
           std::function<bool(std::vector<Phoneme>&)>& condition):
    name_(name), condition_(condition) {}