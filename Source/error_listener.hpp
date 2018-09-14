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

#ifndef ELEKTRA_PLUGIN_YAWN_ERROR_LISTENER_HPP
#define ELEKTRA_PLUGIN_YAWN_ERROR_LISTENER_HPP

#include <iostream>

#include <yaep.h>

class ErrorListener {
public:
  void syntaxError(int errorToken, void *errorTokenData __attribute__((unused)),
                   int ignoredToken,
                   void *ignoredTokenData __attribute__((unused)),
                   int recoveredToken,
                   void *recoveredTokenData __attribute__((unused))) {
    std::cerr << "Syntax error on token number" << errorToken << "”"
              << std::endl;
    if (ignoredToken > 0) {
      std::cerr << "Ignoring " << (recoveredToken - ignoredToken)
                << " tokens starting with token number " << ignoredToken << "”"
                << std::endl;
    }
  }
};

#endif // ELEKTRA_PLUGIN_YAWN_ERROR_LISTENER_HPP
