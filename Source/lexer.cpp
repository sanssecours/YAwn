/**
 * @file
 *
 * @brief This file contains the implementation of a basic YAML lexer.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

// -- Class --------------------------------------------------------------------

int Lexer::nextToken(void **attribute);
{
  if (end) {
    return -1;
  }

  *attribute = NULL;
  end = true;
  return '1';
}
