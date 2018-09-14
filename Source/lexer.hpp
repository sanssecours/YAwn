/**
 * @file
 *
 * @brief This file contains a basic YAML lexer.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

#ifndef ELEKTRA_PLUGIN_YAWN_LEXER_HPP
#define ELEKTRA_PLUGIN_YAWN_LEXER_HPP

class Lexer {
  size_t token = 0;

public:
  int nextToken(void **attribute __attribute__((unused))) {
    const char input[] = "1+1";

    token++;
    *attribute = NULL;
    if (static_cast<size_t>(token) < sizeof(input)) {
      return input[token - 1];
    }
    return -1;
  }
};

#endif // ELEKTRA_PLUGIN_YAWN_LEXER_HPP
