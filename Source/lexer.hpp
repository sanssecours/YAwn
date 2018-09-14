/**
 * @file
 *
 * @brief This file contains definitions for a basic YAML lexer.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

#ifndef ELEKTRA_PLUGIN_YAWN_LEXER_HPP
#define ELEKTRA_PLUGIN_YAWN_LEXER_HPP

class Lexer {
  /** This variable specifies if the parser found the end of the input. */
  bool end = false;

public:
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
