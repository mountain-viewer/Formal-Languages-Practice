//
// Created by whoami on 10/26/16.
//

#ifndef REGULAR_EXPRESSION_PRACTICE_REGULAREXPRESSIONPARSER_H
#define REGULAR_EXPRESSION_PRACTICE_REGULAREXPRESSIONPARSER_H

#include <string>

// Will be thrown if input string is not a regular expression
const std::string kErrorMessage = "Parsing exception: "
    "The passed argument can't be interpreted as a regular expression.";

enum class Token : char {
  kEmptyWord = '1',
  kAlternative = '+',
  kConcatenate = '.',
  kMultipleOccurrence = '*'
};

// Keep track of regular expression properties
struct StackState {
  StackState() : suitable_word_len(0), suffix_len(0) { }

  StackState(int _suitable_word_len, int _suffix_len)
      : suitable_word_len(_suitable_word_len), suffix_len(_suffix_len) { }

  int suitable_word_len;
  int suffix_len;
};

// Main logic class
// Provide interface for solving task
class RegularExpressionParser {
 public:
  RegularExpressionParser() = delete;

  RegularExpressionParser(const std::string& regular_expression, char gen_symbol, int suffix_length)
      : regular_expression_(regular_expression), gen_symbol_(gen_symbol), suffix_length_(suffix_length) { }

  // Traverse the regular expression, determine if it is correct and solve the given task
  bool ParseAndCheckIfContains() const;

 private:

  // Check if a character is from given alphabet
  bool CheckIfCorrectLetter(char ch) const;

  // Handle operators
  StackState PerformChoosingAlternative(const StackState& lhs, const StackState& rhs) const;
  StackState PerformConcatenating(const StackState& lhs, const StackState& rhs) const;
  StackState PerformProcessMultipleOccurrence(const StackState& operand) const;

  std::string regular_expression_;
  char gen_symbol_;
  int suffix_length_;
};


#endif //REGULAR_EXPRESSION_PRACTICE_REGULAREXPRESSIONPARSER_H
