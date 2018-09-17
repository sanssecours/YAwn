/**
 * @file
 *
 * @brief This file contains the implementation of a basic tree walker.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

// -- Imports ------------------------------------------------------------------

#include <iostream>

#include "walker.hpp"

using std::cout;
using std::endl;
using std::string;

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
    return "Nil";
  case yaep_tree_node_type::YAEP_ERROR:
    return "Error";
  case yaep_tree_node_type::YAEP_TERM:
    return "Terminal";
  case yaep_tree_node_type::YAEP_ANODE:
    return "Abstract Node";
  case yaep_tree_node_type::YAEP_ALT:
    return "Alternative";
  }
  return "Unknown";
}

} // namespace

// -- Class --------------------------------------------------------------------

/**
 * @brief This method walks a syntax tree to produce some useful information.
 *
 * @param root This variable stores the root of the tree this function visits.
 */
void Walker::walk(yaep_tree_node const *root) {
  cout << "Type of top node: " << toString(root) << endl;
  cout << "Code of top node: " << (root->val).term.code << endl;
}
