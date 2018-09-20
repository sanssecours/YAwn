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

// ===========
// = Private =
// ===========

/**
 * @brief This method consumes characters from the input stream keeping
 *        track of line and column numbers.
 *
 * @param characters This parameter specifies the number of characters the
 *                   the function should consume.
 */
void Lexer::forward(size_t const characters = 1) {
  LOGF("Forward {} characters", characters);

  for (size_t charsLeft = characters; charsLeft > 0; charsLeft--) {
    if (input.LA(1) == 0) {
      LOG("Hit EOF!");
      return;
    }

    location += 1;
    if (input.LA(1) == '\n') {
      location.end.column = 1;
      location.lines();
    }
    input.consume();
  }
}

/**
 * @brief This method removes uninteresting characters from the input.
 */
void Lexer::scanToNextToken() {
  LOG("Scan to next token");
  bool found = false;
  while (!found) {
    while (input.LA(1) == ' ') {
      forward();
    }
    LOG("Skipped whitespace");
    if (input.LA(1) == '\n') {
      forward();
      LOG("Skipped newline");
    } else {
      found = true;
      LOG("Found next token");
    }
  }
}

/**
 * @brief This method adds new tokens to the token queue.
 */
void Lexer::fetchTokens() {
  scanToNextToken();
  location.step();
  // addBlockEnd(location.begin.column);
  LOGF("Fetch new token at location: {}:{}", location.begin.line,
       location.begin.column);

  // if (input.LA(1) == 0) {
  //   scanEnd();
  //   return;
  // } else if (isValue()) {
  //   scanValue();
  //   return;
  // } else if (isElement()) {
  //   scanElement();
  //   return;
  // } else if (input.LA(1) == '"') {
  //   scanDoubleQuotedScalar();
  //   return;
  // } else if (input.LA(1) == '\'') {
  //   scanSingleQuotedScalar();
  //   return;
  // } else if (input.LA(1) == '#') {
  //   scanComment();
  //   return;
  // }

  // scanPlainScalar();

  tokens.push_back(createToken(Token::PLAIN_SCALAR, location, "Hello World"));
  scanEnd();
}

/**
 * @brief This method adds the token for the start of the YAML stream to
 *        the token queue.
 */
void Lexer::scanStart() {
  LOG("Scan start token");
  tokens.push_back(createToken(Token::STREAM_START, location, "STREAM START"));
}

/**
 * @brief This method adds the token for the end of the YAML stream to
 *        the token queue.
 */
void Lexer::scanEnd() {
  LOG("Scan end token");
  // addBlockEnd(0);
  tokens.push_back(createToken(Token::STREAM_END, location, "STREAM END"));
  tokens.push_back(createToken(-1, location, "EOF"));
  done = true;
}

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

  scanStart();
  fetchTokens();
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
