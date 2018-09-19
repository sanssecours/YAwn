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

#include "location.hpp"
#include "token.hpp"

// -- Class --------------------------------------------------------------------

class Token {

  /** This attribute stores a number representing the kind of the token. */
  int _type;

  /** This variable stores the content stored inside the token. */
  std::string _text;

  /** This variable stores the location of this token in the scanned text. */
  Location location;

public:
  /** This token type starts the YAML stream. */
  static const int STREAM_START = 1;
  /** This token type ends the YAML stream. */
  static const int STREAM_END = 2;
  /** This token type specifies that the token stores a plain scalar. */
  static const int PLAIN_SCALAR = 3;

  /**
   * @brief This function returns a string representation of a token.
   *
   * @param token This argument specifies the token for which this function
   *              creates a string representation.
   *
   * @return A text representing the given token
   **/
  friend std::string to_string(Token token);

  /**
   * @brief This constructor creates a token from the given arguments.
   *
   * @param type This number specifies the type of the token.
   * @param text This variable specifies the content that should be stored
   *             in the token.
   */
  Token(int const type, std::string const &text);

  /**
   * @brief This method returns the type of the token.
   *
   * @return A number specifying the type of this token
   */
  int getType() const;

  /**
   * @brief This method returns the content of the token.
   *
   * @return The text stored inside this token
   */
  std::string getText() const;
};

#endif // ELEKTRA_PLUGIN_YAWN_TOKEN_HPP
