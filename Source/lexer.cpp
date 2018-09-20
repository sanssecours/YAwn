/**
 * @file
 *
 * @brief This file contains the implementation of a basic YAML lexer.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

// -- Imports ------------------------------------------------------------------

#include <stdexcept>

#include "lexer.hpp"

using std::ifstream;
using std::make_pair;
using std::runtime_error;
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
 * @brief This method checks if the input at the specified offset starts a key
 *        value token.
 *
 * @param offset This parameter specifies an offset to the current position,
 *               where this function will look for a key value token.
 *
 * @retval true If the input matches a key value token
 * @retval false Otherwise
 */
bool Lexer::isValue(size_t const offset) const {
  return (input.LA(offset) == ':') &&
         (input.LA(offset + 1) == '\n' || input.LA(offset + 1) == ' ');
}

/**
 * @brief This method checks if the current input starts a list element.
 *
 * @retval true If the input matches a list element token
 * @retval false Otherwise
 */
bool Lexer::isElement() const {
  return (input.LA(1) == '-') && (input.LA(2) == '\n' || input.LA(2) == ' ');
}

/**
 * @brief This method checks if the input at the specified offset starts a line
 *        comment.
 *
 * @param offset This parameter specifies an offset to the current position,
 *               where this function will look for a comment token.
 *
 * @retval true If the input matches a comment token
 * @retval false Otherwise
 */
bool Lexer::isComment(size_t const offset) const {
  return (input.LA(offset) == '#') &&
         (input.LA(offset + 1) == '\n' || input.LA(offset + 1) == ' ');
}

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
 * @brief This method adds block closing tokens to the token queue, if the
 *        indentation decreased.
 *
 * @param lineIndex This parameter specifies the column (indentation in number
 *                  of spaces) for which this method should add block end
 *                  tokens.
 */
void Lexer::addBlockEnd(size_t const lineIndex) {
  while (lineIndex < indents.top()) {
    LOG("Add block end");
    tokens.push_back(createToken(Token::BLOCK_END, location, "BLOCK END"));
    indents.pop();
  }
}

/**
 * @brief This function adds an indentation value if the given value is smaller
 *        than the current indentation.
 *
 * @param lineIndex This parameter specifies the indentation value that this
 *                  function compares to the current indentation.
 *
 * @retval true If the function added an indentation value
 * @retval false Otherwise
 */
bool Lexer::addIndentation(size_t const lineIndex) {
  if (lineIndex > indents.top()) {
    LOGF("Add indentation {}", lineIndex);
    indents.push(lineIndex);
    return true;
  }
  return false;
}

/**
 * @brief This method saves a token for a simple key candidate located at the
 *        current input position.
 */
void Lexer::addSimpleKeyCandidate() {
  size_t position = tokens.size() + emitted.size();
  simpleKey = make_pair(createToken(Token::KEY, location, "KEY"), position);
}

/**
 * @brief This function checks if the lexer needs to scan additional tokens.
 *
 * @retval true If the lexer should fetch additional tokens
 * @retval false Otherwise
 */
bool Lexer::needMoreTokens() const {
  if (done) {
    return false;
  }

  bool keyCandidateExists = simpleKey.first != nullptr;
  return keyCandidateExists || tokens.empty();
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
  addBlockEnd(location.begin.column);
  LOGF("Fetch new token at location: {}:{}", location.begin.line,
       location.begin.column);

  if (input.LA(1) == 0) {
    scanEnd();
    return;
  } else if (isValue()) {
    scanValue();
    return;
  } else if (isElement()) {
    scanElement();
    return;
  } else if (input.LA(1) == '"') {
    scanDoubleQuotedScalar();
    return;
  } else if (input.LA(1) == '\'') {
    scanSingleQuotedScalar();
    return;
  }
  // else if (input.LA(1) == '#') {
  //   scanComment();
  //   return;
  // }

  scanPlainScalar();
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
  addBlockEnd(0);
  tokens.push_back(createToken(Token::STREAM_END, location, "STREAM END"));
  tokens.push_back(createToken(-1, location, "EOF"));
  done = true;
}

/**
 * @brief This method scans a single quoted scalar and adds it to the token
 *        queue.
 */
void Lexer::scanSingleQuotedScalar() {
  LOG("Scan single quoted scalar");

  size_t start = input.index();
  // A single quoted scalar can start a simple key
  addSimpleKeyCandidate();

  forward(); // Include initial single quote
  while (input.LA(1) != '\'' || input.LA(2) == '\'') {
    forward();
  }
  forward(); // Include closing single quote
  tokens.push_back(
      createToken(Token::SINGLE_QUOTED_SCALAR, location, input.getText(start)));
}

/**
 * @brief This method scans a double quoted scalar and adds it to the token
 *        queue.
 */
void Lexer::scanDoubleQuotedScalar() {
  LOG("Scan double quoted scalar");
  size_t start = input.index();

  // A double quoted scalar can start a simple key
  addSimpleKeyCandidate();

  forward(); // Include initial double quote
  while (input.LA(1) != '"') {
    forward();
  }
  forward(); // Include closing double quote
  tokens.push_back(
      createToken(Token::DOUBLE_QUOTED_SCALAR, location, input.getText(start)));
}

/**
 * @brief This method scans a plain scalar and adds it to the token queue.
 */
void Lexer::scanPlainScalar() {
  LOG("Scan plain scalar");
  // A plain scalar can start a simple key
  addSimpleKeyCandidate();

  size_t lengthSpace = 0;
  size_t lengthNonSpace = 0;
  size_t start = input.index();

  while (true) {
    lengthNonSpace = countPlainNonSpace(lengthSpace);
    if (lengthNonSpace == 0) {
      break;
    }
    forward(lengthSpace + lengthNonSpace);
    lengthSpace = countPlainSpace();
  }

  tokens.push_back(
      createToken(Token::PLAIN_SCALAR, location, input.getText(start)));
}

/**
 * @brief This method counts the number of non space characters that can be part
 *        of a plain scalar at position `offset`.
 *
 * @param offset This parameter specifies an offset to the current input
 *               position, where this function searches for non space
 *               characters.
 *
 * @return The number of non-space characters at the input position `offset`
 */
size_t Lexer::countPlainNonSpace(size_t const offset) const {
  LOG("Scan non space characters");
  string const stop = " \n";

  size_t lookahead = offset + 1;
  while (stop.find(input.LA(lookahead)) == string::npos &&
         input.LA(lookahead) != 0 && !isValue(lookahead) &&
         !isComment(lookahead)) {
    lookahead++;
  }

  LOGF("Found {} non-space characters", lookahead - offset - 1);
  return lookahead - offset - 1;
}

/**
 * @brief This method counts the number of space characters that can be part
 *        of a plain scalar at the current input position.
 *
 * @return The number of space characters at the current input position
 */
size_t Lexer::countPlainSpace() const {
  LOG("Scan spaces");
  size_t lookahead = 1;
  while (input.LA(lookahead) == ' ') {
    lookahead++;
  }
  LOGF("Found {} space characters", lookahead - 1);
  return lookahead - 1;
}

/**
 * @brief This method scans a mapping value token and adds it to the token
 *        queue.
 */
void Lexer::scanValue() {
  LOG("Scan value");
  forward(1);
  tokens.push_back(
      createToken(Token::VALUE, location, input.getText(input.index() - 1)));
  forward(1);
  if (simpleKey.first == nullptr) {
    throw runtime_error("Unable to locate key for value");
  }
  size_t offset = simpleKey.second - emitted.size();
  auto key = move(simpleKey.first);
  auto start = key->getStart();
  tokens.insert(tokens.begin() + offset, move(key));
  simpleKey.first = nullptr; // Remove key candidate
  if (addIndentation(start.column)) {
    location.begin = start;
    tokens.insert(tokens.begin() + offset,
                  createToken(Token::MAPPING_START, location, "MAPPING START"));
  }
}

/**
 * @brief This method scans a list element token and adds it to the token
 *        queue.
 */
void Lexer::scanElement() {
  LOG("Scan element");
  if (addIndentation(location.end.column)) {
    tokens.push_back(
        createToken(Token::SEQUENCE_START, location, "SEQUENCE START"));
  }
  forward(1);
  tokens.push_back(
      createToken(Token::ELEMENT, location, input.getText(input.index() - 1)));
  forward(1);
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
  while (needMoreTokens()) {
    fetchTokens();
  }
  string output;
  output += "\n\nTokens:\n";
  for (auto const &token : tokens) {
    output += "\t" + to_string(*token) + "\n";
  }
  LOG(output);

  if (tokens.size() <= 0) {
    tokens.push_front(createToken(-1, location, "EOF"));
  }

  emitted.push_back(move(tokens.front()));
  tokens.pop_front();

  *attribute = &emitted.back();
  return emitted.back()->getType();
}
