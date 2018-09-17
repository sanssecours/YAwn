/**
 * @file
 *
 * @brief This file implements an error listener for the YAML parser.
 *
 * About 50 percent of this code was copied from YAEP’s test suite.
 *
 * @copyright GPL License
 *            (see https://github.com/vnmakarov/yaep/blob/master/copyright)
 */

// -- Imports ------------------------------------------------------------------

#include <iostream>

#include <yaep.h>

#include "error_listener.hpp"

using std::cerr;
using std::endl;

// -- Class --------------------------------------------------------------------

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
void ErrorListener::syntaxError(
    int errorToken, void *errorTokenData __attribute__((unused)),
    int ignoredToken, void *ignoredTokenData __attribute__((unused)),
    int recoveredToken, void *recoveredTokenData __attribute__((unused))) {
  cerr << "Syntax error on token number " << errorToken << "”" << endl;
  if (ignoredToken > 0) {
    cerr << "Ignoring " << (recoveredToken - ignoredToken)
         << " tokens starting with token number " << ignoredToken << "”"
         << endl;
  }
}
