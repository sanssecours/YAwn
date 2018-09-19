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
