// -- Imports ------------------------------------------------------------------

#include <iostream>
#include <stdlib.h>

#include <kdb.hpp>

#include "convert.hpp"

using ckdb::keyNew;
using kdb::Key;
using kdb::KeySet;

using std::cout;
using std::endl;

// -- Functions ----------------------------------------------------------------

void printOutput(KeySet const &keys) {
  cout << endl << "— Output ————" << endl << endl;
  for (auto key : keys) {
    cout << key.getName() << ":"
         << (key.getStringSize() > 1 ? " " + key.getString() : "") << endl;
  }
}

// -- Main ---------------------------------------------------------------------

int main() {
  KeySet keys;
  Key parent{keyNew("user", KEY_END, "", KEY_VALUE)};

  int status = addToKeySet(keys, parent, "");
  printOutput(keys);
  return (status >= 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
