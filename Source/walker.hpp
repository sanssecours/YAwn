/**
 * @file
 *
 * @brief This file contains a basic tree walker.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

#ifndef ELEKTRA_PLUGIN_YAWN_WALKER_HPP
#define ELEKTRA_PLUGIN_YAWN_WALKER_HPP

#include <iostream>

#include <yaep.h>

static std::string toString(yaep_tree_node const *node) {
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

class Walker {
public:
  void walk(yaep_tree_node const *root) {
    std::cout << "Type of top node: " << toString(root) << std::endl;
    std::cout << "Code of top node: " << (root->val).term.code << std::endl;
  }
};

#endif // ELEKTRA_PLUGIN_YAWN_WALKER_HPP
