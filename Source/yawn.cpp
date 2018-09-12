/*
 * Original Source:
 *
 *  https://github.com/vnmakarov/yaep/blob/master/src/yaep++.tst.in
 *
 *   Copyright (C) 1997-2015 Vladimir Makarov.
 *
 *   Written by Vladimir Makarov <vmakarov@gcc.gnu.org>
 *
 *   This is part of YAEP (Yet Another Earley Parser) implementation; you can
 *   redistribute it and/or modify it under the terms of the GNU General
 *   Public License as published by the Free Software Foundation; either
 *   version 2, or (at your option) any later version.
 *
 *   This software is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with GNU CC; see the file COPYING.  If not, write to the Free
 *   Software Foundation, 59 Temple Place - Suite 330, Boston, MA
 *   02111-1307, USA.
 *
 */

#include "objstack.h"
#include <cstdlib>
#include <iostream>
#include <yaep.h>

using std::cerr;
using std::endl;

/* All parser allocated memory is contained here. */
static os_t parseTreeMemory;

static void *allocate(int size) {
  void *result;

  parseTreeMemory.top_expand(size);
  result = parseTreeMemory.top_begin();
  parseTreeMemory.top_finish();
  return result;
}

/* Print syntax error. */
static void
syntaxError(int errorToken, void *errorTokenAttribute __attribute__((unused)),
            int firstIgnoredToken,
            void *firstIgnoredTokenAttribute __attribute__((unused)),
            int firstRecoveredToken,
            void *firstRecoveredTokenAttribute __attribute__((unused))) {
  cerr << "Syntax error on token “" << errorToken << "”" << endl;
  if (firstIgnoredToken > 0) {
    cerr << "Ignoring " << (firstRecoveredToken - firstIgnoredToken)
         << " tokens starting with token “" << firstIgnoredToken << "”" << endl;
  }
}

/* The following variable stores the index of next input token. */
static int token;

static int readToken(void **attribute) {
  const char input[] = "1+1";

  token++;
  *attribute = NULL;
  if (static_cast<size_t>(token) < sizeof(input)) {
    return input[token - 1];
  }
  return -1;
}

static const char *description = "\n"
                                 "TERM\n"
                                 "NUMBER = 49;\n"
                                 "E : T         # 0\n"
                                 "  | E '+' T   # plus (0 2)\n"
                                 "  ;\n"
                                 "T : F         # 0\n"
                                 "  | T '*' F   # mult (0 2)\n"
                                 "  ;\n"
                                 "F : NUMBER    # 0\n"
                                 "  | '(' E ')' # 1\n"
                                 "  ;\n";

int main() {
  yaep parser;
  struct yaep_tree_node *root;
  int ambiguousInput;

  token = 0;
  if (parser.parse_grammar(1, description) != 0) {
    cerr << "Unable to parse grammar:" << parser.error_message() << endl;
    return EXIT_FAILURE;
  }
  if (parser.parse(readToken, syntaxError, allocate, NULL, &root,
                    &ambiguousInput)) {
    cerr << "Unable to parse input: " << parser.error_message() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
