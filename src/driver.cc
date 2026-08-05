#include <array>
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

#include "Consonant.hpp"
#include "English.hpp"
#include "Language.hpp"
#include "Rule.hpp"
#include "Syllable.hpp"
#include "Vowel.hpp"
#include "Word.hpp"

constexpr std::string_view kLogFilename{"error_words.txt"};
constexpr std::string_view kInvalidFilename{"invalid.txt"};

std::vector<std::wstring> Split(const std::wstring& s) {
  std::wistringstream iss{s};
  std::vector<std::wstring> tokens;
  std::wstring token;
  while (iss >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

int main() {
  // NOLINTBEGIN(readability-identifier-naming)

  const Language English{EnglishLang::BuildEnglish()};

  std::cout << "Built language" << std::endl;

  std::wifstream dict{"cmudict.dict"};
  if (!dict) throw std::runtime_error("Could not open file");

  std::vector<std::wstring> lines;
  std::wstring line;
  while (std::getline(dict, line)) {
    lines.push_back(std::move(line));
  }

  std::cout << "Loaded dictionary of " << lines.size() << " lines into memory"
            << std::endl;

  const size_t kThreadCount{std::thread::hardware_concurrency()};
  const size_t kChunkSize{(lines.size() + kThreadCount - 1) / kThreadCount};

  std::map<std::wstring, Word> dictionary;
  std::vector<std::wstring> error;

  std::vector<std::jthread> threads;
  std::vector<std::pair<std::wstring, std::wstring>> invalid_words;

  std::mutex dict_m;
  std::mutex err_m;
  std::mutex inv_m;

  for (size_t t{}; t < kThreadCount; ++t) {
    size_t begin{t * kChunkSize};
    size_t end{std::min(begin + kChunkSize, lines.size())};

    if (begin >= end) continue;

    threads.emplace_back([&, begin, end] {
      for (size_t j{begin}; j < end; ++j) {
        try {
          const std::vector<std::wstring> tokens{Split(lines.at(j))};
          std::vector<Syllable> syllables{
              English.GetSyllablesFromTokens(tokens)};
          Word word{syllables};

          const ValidationResult validation = English.Validate(word);
          if (!validation.valid) {
            std::lock_guard<std::mutex> lock(inv_m);
            invalid_words.push_back({lines.at(j), validation.reason});
            continue;
          }

          std::lock_guard<std::mutex> lock(dict_m);
          dictionary.insert_or_assign(tokens.at(0), word);
        } catch (const std::exception& e) {
          std::lock_guard<std::mutex> lock(err_m);
          error.push_back(lines.at(j) + L" | " + Language::Utf8ToWide(e.what()));
        }
      }
    });
  }

  threads.clear();

  std::cout
      << std::format(
             "Found {} words that could not be constructed, writing to {}.",
             error.size(),
             kLogFilename)
      << std::endl;

  std::wofstream err_ofs{kLogFilename.data()};
  for (const auto& word : error) {
    err_ofs << word << '\n';
  }

  std::cout << std::format("Found {} words that were invalid, writing to {}.",
                           invalid_words.size(),
                           kInvalidFilename)
            << std::endl;

  std::wofstream inv_ofs{kInvalidFilename.data()};
  for (const auto& [w, r] : invalid_words) {
    inv_ofs << w << ": " << r << '\n';
  }

  // NOLINTEND(readability-identifier-naming)
}
