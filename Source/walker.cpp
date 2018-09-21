/**
 * @file
 *
 * @brief This file contains the implementation of a basic tree walker.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

// -- Imports ------------------------------------------------------------------

#include <iostream>
#include <memory>

#include "listener.hpp"
#include "token.hpp"
#include "walker.hpp"

using std::cout;
using std::endl;
using std::move;
using std::string;
using std::to_string;
using std::unique_ptr;

// -- Functions ----------------------------------------------------------------

namespace {

/**
 * @brief This function returns the string representation of a tree node.
 *
 * @param node This argument stores the tree node that this function converts to
 *             a string.
 */
string toString(yaep_tree_node const *const node, string const indent = "") {
  switch (node->type) {
  case yaep_tree_node_type::YAEP_NIL:
    return indent + "<Nil>";
  case yaep_tree_node_type::YAEP_ERROR:
    return indent + "<Error>";
  case yaep_tree_node_type::YAEP_ALT:
    return indent + "<Alternative>";
  default:
    break;
  }

  if (node->type == yaep_tree_node_type::YAEP_TERM) {
    return indent +
           to_string(**(static_cast<unique_ptr<Token> *>(node->val.term.attr)));
  }

  // Node is abstract
  yaep_anode anode = node->val.anode;
  string representation = indent + string("<Abstract Node, ") + anode.name +
                          ", " + to_string(anode.cost) + ">";
  yaep_tree_node **children = anode.children;

  for (size_t child = 0; children[child]; child++) {
    representation += "\n" + toString(children[child], indent + "  ");
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
  cout << "\n— Walk Tree —\n\n";
  cout << toString(root);
  cout << endl;

  Listener listener;
  return listener.getKeySet();
}
