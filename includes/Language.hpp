#include "Phoneme.hpp"
#include "Rule.hpp"
#include "Word.hpp"

class Language {
public:
  void AddPhoneme(Phoneme* phoneme);
  void AddRule(const Rule* rule);
  bool Validate(Word word);

private:
  std::vector<Phoneme> inventory_;
  std::vector<Rule> rules_;
};
