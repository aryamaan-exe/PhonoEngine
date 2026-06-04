#include "Phoneme.hpp"
#include "Rule.hpp"

class Language {
public:
private:
  std::vector<Phoneme> inventory_;
  std::vector<Rule> rules_;
};