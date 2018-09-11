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
#include <yaep.h>

/* All parser allocated memory is contained here. */
static os_t *mem_os;

static void *test_parse_alloc(int size) {
  void *result;

  mem_os->top_expand(size);
  result = mem_os->top_begin();
  mem_os->top_finish();
  return result;
}

/* Print syntax error. */
static void
test_syntax_error(int err_tok_num, void *err_tok_attr __attribute__((unused)),
                  int start_ignored_tok_num,
                  void *start_ignored_tok_attr __attribute__((unused)),
                  int start_recovered_tok_num,
                  void *start_recovered_tok_attr __attribute__((unused))) {
  if (start_ignored_tok_num < 0)
    fprintf(stderr, "Syntax error on token %d\n", err_tok_num);
  else
    fprintf(
        stderr,
        "Syntax error on token %d:ignore %d tokens starting with token = %d\n",
        err_tok_num, start_recovered_tok_num - start_ignored_tok_num,
        start_ignored_tok_num);
}

/* The following variable stores the current number of next input token. */
static int ntok;

static int test_read_token(void **attr) {
  const char input[] = "1+1";

  ntok++;
  *attr = NULL;
  if (static_cast<size_t>(ntok) < sizeof(input))
    return input[ntok - 1];
  else
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
  yaep *e;
  struct yaep_tree_node *root;
  int ambiguous_p;

  mem_os = new os(0);
  e = new yaep();
  if (e == NULL) {
    fprintf(stderr, "yaep::yaep: No memory\n");
    delete mem_os;
    exit(1);
  }
  ntok = 0;
  if (e->parse_grammar(1, description) != 0) {
    fprintf(stderr, "%s\n", e->error_message());
    delete mem_os;
    exit(1);
  }
  if (e->parse(test_read_token, test_syntax_error, test_parse_alloc, NULL,
               &root, &ambiguous_p)) {
    fprintf(stderr, "yaep::parse: %s\n", e->error_message());
    delete mem_os;
    exit(1);
  }
  delete e;
  delete mem_os;
  exit(0);
}
