/**
 * @file
 *
 * @brief This file contains the declaration of a basic YAML converter.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

// -- Class --------------------------------------------------------------------

class Converter {
  const char *grammar = "\n"
                        "TERM\n"
                        "NUMBER = 49;\n"
                        "START : NUMBER # 0\n"
                        "      ;\n";

public:
  int parse();
};
