/**
 * @file
 *
 * @brief This file contains definitions for a basic YAML lexer.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

#ifndef ELEKTRA_PLUGIN_YAWN_LEXER_HPP
#define ELEKTRA_PLUGIN_YAWN_LEXER_HPP

// -- Macros -------------------------------------------------------------------

#define SPDLOG_TRACE_ON

#if defined(__clang__)
#define LOGF(fmt, ...)                                                         \
  console->trace("{}:{}: " fmt, __FUNCTION__, __LINE__, __VA_ARGS__)
#else
#define LOGF(fmt, ...)
#endif

#if defined(__clang__)
#define LOG(text) console->trace("{}:{}: {}", __FUNCTION__, __LINE__, text)
#else
#define LOG(text)
#endif

// -- Imports ------------------------------------------------------------------

#include <deque>
#include <fstream>
#include <memory>
#include <stack>

#include "input.hpp"
#include "token.hpp"

#if defined(__clang__)
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

using spdlog::logger;
using std::shared_ptr;
#endif

// -- Class --------------------------------------------------------------------

/** This class implements a basic lexer for the serialization format YAML. */
class Lexer {
  /** This attribute represents the input the lexer tokenizes. */
  Input input;

  /** This queue stores the list of tokens produced by the lexer. */
  std::deque<std::unique_ptr<Token>> tokens;

  /**
   * This variable stores tokens already emitted by the parser. We keep this
   * list, since the syntax tree produced by YAEP only stores references to
   * tokens. As a consequence we need to keep the referenced tokens in
   * memory, as long as other code accesses the token attributes of the syntax
   * tree.
   */
  std::deque<std::unique_ptr<Token>> emitted;

  /** This variable stores the current line and column number. */
  Location location;

  /**
   * This stack stores the indentation (in number of characters) for each
   * block collection.
   */
  std::stack<size_t> indents{std::deque<size_t>{0}};

  /**
   * This boolean specifies if the lexer has already scanned the whole input or
   * not.
   */
  bool done = false;

#if defined(__clang__)
  /**
   * This variable stores the logger used by the lexer to print debug messages.
   */
  shared_ptr<logger> console;
#endif

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
  bool isValue(size_t const offset = 1) const;

  /**
   * @brief This method checks if the current input starts a list element.
   *
   * @retval true If the input matches a list element token
   * @retval false Otherwise
   */
  bool isElement() const;

  /**
   * @brief This method checks if the input at the specified offset starts a
   *        line comment.
   *
   * @param offset This parameter specifies an offset to the current position,
   *               where this function will look for a comment token.
   *
   * @retval true If the input matches a comment token
   * @retval false Otherwise
   */
  bool isComment(size_t const offset) const;

  /**
   * @brief This method consumes characters from the input stream keeping
   *        track of line and column numbers.
   *
   * @param characters This parameter specifies the number of characters the
   *                   the function should consume.
   */
  void forward(size_t const characters);

  /**
   * @brief This method adds block closing tokens to the token queue, if the
   *        indentation decreased.
   *
   * @param lineIndex This parameter specifies the column (indentation in number
   *                  of spaces) for which this method should add block end
   *                  tokens.
   */
  void addBlockEnd(size_t const lineIndex);

  /**
   * @brief This method removes uninteresting characters from the input.
   */
  void scanToNextToken();

  /**
   * @brief This method adds new tokens to the token queue.
   */
  void fetchTokens();

  /**
   * @brief This method adds the token for the start of the YAML stream to
   *        the token queue.
   */
  void scanStart();

  /**
   * @brief This method adds the token for the end of the YAML stream to
   *        the token queue.
   */
  void scanEnd();

public:
  /**
   * @brief This constructor initializes a lexer with the given input.
   *
   * @param stream This stream specifies the text which this lexer analyzes.
   */
  Lexer(std::ifstream &stream);

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
  int nextToken(void **attribute);
};

#endif // ELEKTRA_PLUGIN_YAWN_LEXER_HPP
