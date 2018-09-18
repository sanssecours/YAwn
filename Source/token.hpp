/**
 * @file
 *
 * @brief This file contains the declaration of a class that stores data
 *        about a token produced by a lexer.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

#ifndef ELEKTRA_PLUGIN_YAWN_TOKEN_HPP
#define ELEKTRA_PLUGIN_YAWN_TOKEN_HPP

// -- Imports ------------------------------------------------------------------

#include <string>

#include "token.hpp"

// -- Class --------------------------------------------------------------------

class Token {

  /** This variable stores the content stored inside the token. */
  std::string text;

  Token(std::string const &content);
};

#endif // ELEKTRA_PLUGIN_YAWN_TOKEN_HPP
