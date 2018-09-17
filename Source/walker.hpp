/**
 * @file
 *
 * @brief This file contains the declaration of a basic tree walker.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

#ifndef ELEKTRA_PLUGIN_YAWN_WALKER_HPP
#define ELEKTRA_PLUGIN_YAWN_WALKER_HPP

// -- Imports ------------------------------------------------------------------

#include <yaep.h>

// -- Class --------------------------------------------------------------------

/** This class contains a method to walk a YAEP syntax tree. */
class Walker {
public:
  /**
   * @brief This method walks a syntax tree to produce some useful information.
   *
   * @param root This variable stores the root of the tree this function visits.
   */
  void walk(yaep_tree_node const *root);
};

#endif // ELEKTRA_PLUGIN_YAWN_WALKER_HPP
