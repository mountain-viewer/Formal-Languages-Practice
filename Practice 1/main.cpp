#include <iostream>

#include "RegularExpressionParser.h"

// Algorithm is explained more deeply in README.md

void run() {

  std::string regular_expression;
  char gen_symbol;
  int suffix_length;

  std::cout << "Enter the regular expression in reverse polish notation:" << std::endl;
  std::cin >> regular_expression;

  std::cout << "Enter the suffix symbol:" << std::endl;
  std::cin >> gen_symbol;

  std::cout << "Enter the length of suffix:" << std::endl;
  std::cin >> suffix_length;

  RegularExpressionParser regular_expression_parser(regular_expression, gen_symbol, suffix_length);

  try {
    std::cout << (regular_expression_parser.ParseAndCheckIfContains() ? "YES" : "NO") << std::endl;
  } catch (std::string e) {
    std::cout << e << std::endl;
  }
}

int main() {
  run();
  return 0;
}