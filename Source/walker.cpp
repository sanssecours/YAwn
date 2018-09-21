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

using std::cerr;
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

/**
 * @brief This function traverses a tree executing methods of a listener class.
 *
 * @param listener The function calls methods of this class while it traverses
 *                 the tree.
 *
 * @param node This argument stores the tree node that this function traverses.
 */
void executeListenerMethods(Listener &listener, yaep_tree_node const *node) {
  if (node->type == yaep_tree_node_type::YAEP_TERM ||
      node->type == yaep_tree_node_type::YAEP_NIL) {
    return;
  }
  assert(node->type == yaep_tree_node_type::YAEP_ANODE &&
         "Found unexpected node type");

  // Node is abstract
  yaep_anode anode = node->val.anode;

  if (string(anode.name) == "value") {
    auto token = anode.children[0]->val.term.attr;
    listener.exitValue((**static_cast<unique_ptr<Token> *>(token)).getText());
    return;
  }

  yaep_tree_node **children = anode.children;
  for (size_t child = 0; children[child]; child++) {
    executeListenerMethods(listener, children[child]);
  }
}

} // namespace

// -- Class --------------------------------------------------------------------

/**
 * @brief This method walks a syntax tree calling methods of the given
 *        listener.
 *
 * @param listener This argument specifies the listener which this function
 *                 uses to convert the syntax tree to a key set.
 * @param root This variable stores the root of the tree this function visits.
 */
void Walker::walk(Listener &listener, yaep_tree_node const *root) {
  cout << "\n— Syntax Tree —\n\n";
  cout << toString(root);
  cout << endl;

  executeListenerMethods(listener, root);
}
