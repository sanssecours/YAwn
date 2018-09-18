/**
 * @file
 *
 * @brief This file contains the implementation of a basic tree walker.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

// -- Imports ------------------------------------------------------------------

#include <iostream>

#include "token.hpp"
#include "walker.hpp"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

// -- Functions ----------------------------------------------------------------

namespace {

/**
 * @brief This function returns the string representation of a tree node.
 *
 * @param node This argument stores the tree node that this function converts to
 *              a string.
 */
string toString(yaep_tree_node const *node) {
  switch (node->type) {
  case yaep_tree_node_type::YAEP_NIL:
    return "<Nil>";
  case yaep_tree_node_type::YAEP_ERROR:
    return "<Error>";
  case yaep_tree_node_type::YAEP_TERM:
    return "<Terminal, " + to_string(node->val.term.code) + ", " +
           static_cast<Token *>(node->val.term.attr)->getText() + ">";
  case yaep_tree_node_type::YAEP_ALT:
    return "<Alternative>";
  default:
    break;
  }
  // Node is abstract
  yaep_anode anode = node->val.anode;
  string representation = string("<Abstract Node, ") + anode.name + ", " +
                          to_string(anode.cost) + ">";
  yaep_tree_node **child = anode.children;

  while (child) {
    representation += toString(*child);
  }

  return representation;
}

} // namespace

// -- Class --------------------------------------------------------------------

/**
 * @brief This method walks a syntax tree to produce some useful information.
 *
 * @param root This variable stores the root of the tree this function visits.
 */
kdb::KeySet Walker::walk(yaep_tree_node const *root) {
  cout << "— Walk Tree —\n\n";
  cout << toString(root);
  cout << endl;

  return keys;
}
