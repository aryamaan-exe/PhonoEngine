#include <Language.hpp>
#include <fstream>
#include <iostream>

#ifdef CATCH_CONFIG_MAIN
#  undef CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

bool CompareFiles(const std::string& filename1, const std::string& filename2) {
  std::ifstream ifs1{filename1, std::ios::binary};
  std::ifstream ifs2{filename2, std::ios::binary};

  if (!ifs1.is_open() || !ifs2.is_open()) return false;

  std::ostringstream ss1, ss2;
  ss1 << ifs1.rdbuf();
  ss2 << ifs2.rdbuf();

  return ss1.str() == ss2.str();
}

TEST_CASE("Load language from file", "[file]") {
  Language test_lang{"test_lang.json"};
  test_lang.AddRule(new Rule{
      L"Test rule", RuleType::Onset, [](const SyllablePart&) { return true; }});

  std::wofstream ofs{"test_lang_out.txt"};
  ofs << test_lang;

  REQUIRE(CompareFiles("test_lang_out.txt", "correct_test_lang_out.txt"));
}