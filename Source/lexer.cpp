/**
 * @file
 *
 * @brief This file contains the implementation of a basic YAML lexer.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

// -- Imports ------------------------------------------------------------------

#include "lexer.hpp"

using std::ifstream;

// -- Class --------------------------------------------------------------------

/**
 * @brief This constructor initializes a lexer with the given input.
 *
 * @param stream This stream specifies the text which this lexer analyzes.
 */
Lexer::Lexer(ifstream &stream) : input{stream} {
  tokens.push_back(Token('1', "Hello World"));
}

/**
 * @brief This method returns the number of the next token produced by the
 *        lexer.
 *
 * If the lexer found the end of the input, then this function returns `-1`.
 *
 * @param attribute The parser uses this parameter to store auxiliary data for
 *                  the returned token.
 *
 * @return The number of the first token the parser has not emitted yet.
 */
int Lexer::nextToken(void **attribute) {
  if (tokens.size() <= 0) {
    tokens.push_front(Token(-1, "EOF"));
  }

  *attribute = &tokens.front();
  int kind = tokens.front().getType();
  tokens.pop_front();
  return kind;
}
