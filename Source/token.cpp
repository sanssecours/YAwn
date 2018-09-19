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

/**
 * @brief This constructor creates a token from the given arguments.
 *
 * @param type This number specifies the type of the token.
 * @param text This variable specifies the content that should be stored
 *             in the token.
 */
Token::Token(int const type, std::string const &text)
    : _type{type}, _text{text} {}

/**
 * @brief This method returns the type of the token.
 *
 * @return A number specifying the type of this token
 */
int Token::getType() const { return _type; }

/**
 * @brief This method returns the content of the token.
 *
 * @return The text stored inside this token
 */
string Token::getText() const { return _text; }
