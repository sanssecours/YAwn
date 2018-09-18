/**
 * @file
 *
 * @brief This file contains the implementation of a class that stores data
 *        about a token produced by a lexer.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

// -- Imports ------------------------------------------------------------------

#include "token.hpp"

using std::string;

// -- Class --------------------------------------------------------------------

Token::Token(string const &content) : text{content} {}
