/**
 * @file
 *
 * @brief This file contains the declaration of a basic listener.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

#ifndef ELEKTRA_PLUGIN_YAWN_LISTENER_HPP
#define ELEKTRA_PLUGIN_YAWN_LISTENER_HPP

// -- Imports ------------------------------------------------------------------

#include <kdb.hpp>

#include <yaep.h>

// -- Class --------------------------------------------------------------------

/**
 * @brief This class contains methods to create a key set.
 *
 * The tree walker (`walker`) calls the various methods of this class to create
 * a key set from the syntax tree created by the parser (`convert`).
 */
class Listener {
  /** This variable stores the key set that this listener creates. */
  kdb::KeySet keys;

public:
  /**
   * @brief This method returns the key set of the listener.
   *
   * @return A key set created by the walker by calling methods of this class
   **/
  kdb::KeySet getKeySet() const;
};

#endif // ELEKTRA_PLUGIN_YAWN_LISTENER_HPP
