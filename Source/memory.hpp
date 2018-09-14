/**
 * @file
 *
 * @brief This file contains a wrapper for YAEP’s `objstack`.
 *
 * About 50 percent of this code was copied from YAEP’s test suite.
 *
 * @copyright GPL License
 *            (see https://github.com/vnmakarov/yaep/blob/master/copyright)
 */

#ifndef ELEKTRA_PLUGIN_YAWN_MEMORY_HPP
#define ELEKTRA_PLUGIN_YAWN_MEMORY_HPP

#include "objstack.h"

class Memory {
  /* All parser allocated memory is contained in this class. */
  os_t parseTreeMemory;

public:
  void *allocate(int size) {
    void *result;

    parseTreeMemory.top_expand(size);
    result = parseTreeMemory.top_begin();
    parseTreeMemory.top_finish();

    return result;
  }
};

#endif // ELEKTRA_PLUGIN_YAWN_MEMORY_HPP
