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
   * @brief This method walks a syntax tree calling methods of the given
   *        listener.
   *
   * @param listener This argument specifies the listener which this function
   *                 uses to convert the syntax tree to a key set.
   * @param root This variable stores the root of the tree this function visits.
   */
  void walk(Listener &listener, yaep_tree_node const *root);
};

#endif // ELEKTRA_PLUGIN_YAWN_WALKER_HPP
