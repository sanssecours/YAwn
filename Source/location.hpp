/**
 * @file
 *
 * @brief This file contains a class specifying the location of a token in a
 *        text.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

#ifndef ELEKTRA_PLUGIN_YAWN_LOCATION_HPP
#define ELEKTRA_PLUGIN_YAWN_LOCATION_HPP

// -- Imports ------------------------------------------------------------------

#include "position.hpp"

// -- Class --------------------------------------------------------------------

/** This class represents the location of a token. */
class Location {
public:
  /** This variable stores the start position of the token. */
  Position begin;
  /** This attribute stores the position where the token ends. */
  Position end;

  /**
   * @brief This method sets the start position to the current end position.
   */
  void step() { begin = end; }
};

#endif // ELEKTRA_PLUGIN_YAWN_LOCATION_HPP
