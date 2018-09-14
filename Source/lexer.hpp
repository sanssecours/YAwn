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
  bool end = false;

public:
  int nextToken(void **attribute) {
    if (end) {
      return -1;
    }

    *attribute = NULL;
    end = true;
    return '1';
  }
};

#endif // ELEKTRA_PLUGIN_YAWN_LEXER_HPP
