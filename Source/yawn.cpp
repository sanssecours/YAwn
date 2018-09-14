// -- Imports ------------------------------------------------------------------

#include <stdlib.h>

#include <kdb.hpp>

#include "convert.hpp"

using ckdb::keyNew;
using kdb::Key;
using kdb::KeySet;

// -- Main ---------------------------------------------------------------------

int main() {
  KeySet keys;
  Key parent{keyNew("user", KEY_END, "", KEY_VALUE)};

  return addToKeySet(keys, parent, "");
}
