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

#include <kdb.hpp>

#include <yaep.h>

// -- Class --------------------------------------------------------------------

/** This class contains a method to convert a YAEP syntax tree for a YAML
    grammar to a key set. */
class Walker {
public:
  /**
   * @brief This method walks a syntax tree to produce some useful information.
   *
   * @param root This variable stores the root of the tree this function visits.
   *
   * @return A key set representing the data stored in the syntax tree
   */
  kdb::KeySet walk(yaep_tree_node const *root);
};

#endif // ELEKTRA_PLUGIN_YAWN_WALKER_HPP
