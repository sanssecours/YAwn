/**
 * @file
 *
 * @brief This file implements an error listener for the YAML parser.
 *
 * About 50 percent of this code was copied from YAEP’s test suite.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

#ifndef ELEKTRA_PLUGIN_YAWN_ERROR_LISTENER_HPP
#define ELEKTRA_PLUGIN_YAWN_ERROR_LISTENER_HPP

// -- Imports ------------------------------------------------------------------

#include <yaep.h>

// -- Class --------------------------------------------------------------------

class ErrorListener {
public:
  /**
   * @brief This method reacts to syntax errors reported by YAEP’s parsing
   *        engine.
   *
   * @param errorToken This number specifies the token where the error occurred.
   * @param errorTokenData This variable stores the data contained in
   *                       `errorToken`.
   * @param ignoredToken This number specifies the first token that was ignored
   *                     during error recovery.
   * @param ignoredTokenData This variable stores the data contained in
   *                         `ignoredToken`.
   * @param recoveredToken This number specifies the first included token after
   *                       the error recovery has taken place.
   * @param recoveredTokenData This variable stores the data contained in
   *                           `recoveredToken`.
   */
  void syntaxError(int errorToken, void *errorTokenData, int ignoredToken,
                   void *ignoredTokenData, int recoveredToken,
                   void *recoveredTokenData);
};

#endif // ELEKTRA_PLUGIN_YAWN_ERROR_LISTENER_HPP
