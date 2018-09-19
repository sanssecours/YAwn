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

#if defined(__clang__)
using spdlog::set_level;
using spdlog::set_pattern;
using spdlog::stderr_color_mt;
using spdlog::level::trace;
#endif

// -- Functions ----------------------------------------------------------------

namespace {

/**
 * Create a token with the given attributes.
 *
 * @param type This number specifies the type of the created token.
 * @param location This number specifies the location of the token in the
 *                 scanned text.
 * @param text This variable specifies the content that should be stored
 *             in the token.
 */
unique_ptr<Token> createToken(int const type, Location const &location,
                              string const &text) {
  return unique_ptr<Token>{new Token{type, location, text}};
}

} // namespace

// -- Class --------------------------------------------------------------------

// ==========
// = Public =
// ==========

/**
 * @brief This constructor initializes a lexer with the given input.
 *
 * @param stream This stream specifies the text which this lexer analyzes.
 */
Lexer::Lexer(ifstream &stream) : input{stream} {
#if defined(__clang__)
  set_pattern("[%H:%M:%S:%e] %v ");
  set_level(trace);
  console = stderr_color_mt("console");
#endif
  LOG("Init lexer");

  tokens.push_back(createToken(Token::STREAM_START, location, "STREAM START"));
  tokens.push_back(createToken(Token::PLAIN_SCALAR, location, "Hello World"));
  tokens.push_back(createToken(Token::STREAM_END, location, "STREAM END"));
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
    tokens.push_front(createToken(-1, location, "EOF"));
  }

  emitted.push_back(move(tokens.front()));
  tokens.pop_front();

  *attribute = &emitted.back();
  return emitted.back()->getType();
}
