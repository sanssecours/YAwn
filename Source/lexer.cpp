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
using std::string;
using std::unique_ptr;

// -- Functions ----------------------------------------------------------------

namespace {

/**
 * Create a token with the given attributes.
 *
 * @param type This number specifies the type of the created token.
 * @param text This variable specifies the content that should be stored
 *             in the token.
 */
unique_ptr<Token> createToken(int const type, string const &text) {
  return unique_ptr<Token>{new Token{type, text}};
}

} // namespace

// -- Class --------------------------------------------------------------------

/**
 * @brief This constructor initializes a lexer with the given input.
 *
 * @param stream This stream specifies the text which this lexer analyzes.
 */
Lexer::Lexer(ifstream &stream) : input{stream} {
  tokens.push_back(createToken(Token::STREAM_START, "STREAM START"));
  tokens.push_back(createToken(Token::PLAIN_SCALAR, "Hello World"));
  tokens.push_back(createToken(Token::STREAM_END, "STREAM END"));
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
    tokens.push_front(createToken(-1, "EOF"));
  }

  emitted.push_back(move(tokens.front()));
  tokens.pop_front();

  *attribute = &emitted.back();
  return emitted.back()->getType();
}
