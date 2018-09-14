static std::string toString(yaep_tree_node *node) {
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
