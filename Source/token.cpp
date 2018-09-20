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
using std::to_string;

// -- Class --------------------------------------------------------------------

/**
 * @brief This constructor creates a token from the given arguments.
 *
 * @param type This number specifies the type of the token.
 * @param location This number specifies the location of the token in the
                   scanned text.
 * @param text This variable specifies the content that should be stored
 *             in the token.
 */
Token::Token(int const type, Location const &location, std::string const &text)
    : _location{location}, _type{type}, _text{text} {}

/**
 * @brief This method returns the type of the token.
 *
 * @return A number specifying the type of this token
 */
int Token::getType() const { return _type; }

/**
 * @brief This method returns the current start position of the token.
 *
 * @return The start position of this token
 */
Position Token::getStart() const { return _location.begin; }

/**
 * @brief This method returns the content of the token.
 *
 * @return The text stored inside this token
 */
string Token::getText() const { return _text; }

/**
 * @brief This function returns a string representation of a token.
 *
 * @param token This argument specifies the token for which this function
 *              creates a string representation.
 *
 * @return A text representing the given token
 **/
string to_string(Token const token) {
  return "<Token, " + to_string(token.getType()) + ", " + token.getText() +
         ", " + to_string(token._location.begin.line) + ":" +
         to_string(token._location.begin.column) + "–" +
         to_string(token._location.end.line) + ":" +
         to_string(token._location.end.column) + ">";
}
