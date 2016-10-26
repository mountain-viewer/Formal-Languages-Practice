//
// Created by whoami on 10/26/16.
//

#include "RegularExpressionParser.h"

#include <stack>
#include <climits>

bool RegularExpressionParser::CheckIfCorrectLetter(char ch) const {
  return ch == 'a' || ch == 'b' || ch == 'c';
}

StackState RegularExpressionParser::
PerformChoosingAlternative(const StackState& lhs, const StackState& rhs) const {

  int suitable_word_len = std::max(lhs.suitable_word_len, rhs.suitable_word_len);
  int suffix_len = std::max(lhs.suffix_len, rhs.suffix_len);

  return StackState(suitable_word_len, suffix_len);
}

StackState RegularExpressionParser::
PerformConcatenating(const StackState& lhs, const StackState& rhs) const {

  int suitable_word_len = -1, suffix_len = -1;

  if (lhs.suitable_word_len >= 0 &&
      rhs.suitable_word_len >= 0) {

    if (lhs.suitable_word_len == INT_MAX ||
        rhs.suitable_word_len == INT_MAX) {
      suitable_word_len = INT_MAX;
    } else {
      suitable_word_len = lhs.suitable_word_len + rhs.suitable_word_len;
    }

  } else {
      suitable_word_len = INT_MIN;
  }

  if (rhs.suitable_word_len >= 0) {
    int tmp = (rhs.suitable_word_len == INT_MAX) ? INT_MAX : lhs.suffix_len + rhs.suitable_word_len;
    suffix_len = std::max(tmp, rhs.suffix_len);
  } else {
    suffix_len = rhs.suffix_len;
  }

  return StackState(suitable_word_len, suffix_len);
}

StackState RegularExpressionParser::
PerformProcessMultipleOccurrence(const StackState& operand) const {

  int suitable_word_len = (operand.suitable_word_len > 0) ? INT_MAX : 0;
  int suffix_len = operand.suffix_len;

  return StackState(suitable_word_len, suffix_len);
}

bool RegularExpressionParser::ParseAndCheckIfContains() const {

  // Stack for processing the regular expression from reverse polish notation
  std::stack<StackState> helper;

  for (auto& symbol : regular_expression_) {
    switch (symbol) {

      case '1': {
        helper.push(StackState(0, 0));
        break;
      }

      case '+': {
        if (helper.size() < 2) {
          throw kErrorMessage;
        }

        StackState right_operand = helper.top();
        helper.pop();

        StackState left_operand = helper.top();
        helper.pop();

        helper.push(PerformChoosingAlternative(left_operand, right_operand));

        break;
      }

      case '.': {
        if (helper.size() < 2) {
          throw kErrorMessage;
        }

        StackState right_operand = helper.top();
        helper.pop();

        StackState left_operand = helper.top();
        helper.pop();

        helper.push(PerformConcatenating(left_operand, right_operand));

        break;
      }

      case '*': {
        if (helper.size() < 1) {
          throw kErrorMessage;
        }

        StackState operand = helper.top();
        helper.pop();

        helper.push(PerformProcessMultipleOccurrence(operand));

        break;
      }

      default: {
        if (!CheckIfCorrectLetter(symbol)) {
          throw kErrorMessage;
        }

        if (symbol == gen_symbol_) {
          helper.push(StackState(1, 1));
        } else {
          helper.push(StackState(INT_MIN, 0));
        }

        break;
      }

    }

  }

  if (helper.size() != 1) {
    throw kErrorMessage;
  }

  return std::max(helper.top().suitable_word_len, helper.top().suffix_len) >= suffix_length_;
}