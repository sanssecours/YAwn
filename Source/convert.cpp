// -- Imports ------------------------------------------------------------------

#include <iostream>

#include <yaep.h>

#include "convert.hpp"
#include "error_listener.hpp"
#include "lexer.hpp"
#include "memory.hpp"
#include "walker.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::string;

using CppKey = kdb::Key;
using CppKeySet = kdb::KeySet;

// -- Globals ------------------------------------------------------------------

static ErrorListener *errorListenerAdress;
static Lexer *lexerAddress;
static Memory *parserMemoryAddress;

// -- Functions ----------------------------------------------------------------

int nextToken(void **attribute) { return lexerAddress->nextToken(attribute); }

void syntaxError(int errorToken, void *errorTokenData, int ignoredToken,
                 void *ignoredTokenData, int recoveredToken,
                 void *recoveredTokenData) {
  return errorListenerAdress->syntaxError(errorToken, errorTokenData,
                                          ignoredToken, ignoredTokenData,
                                          recoveredToken, recoveredTokenData);
}

void *alloc(int size) { return parserMemoryAddress->allocate(size); }

int addToKeySet(CppKeySet &keySet, CppKey &parent, string const &filename) {
  const char *grammar = "\n"
                        "TERM\n"
                        "NUMBER = 49;\n"
                        "START : NUMBER # 0\n"
                        "      ;\n";

  yaep parser;
  struct yaep_tree_node *root = NULL;
  int ambiguousInput;

  if (parser.parse_grammar(1, grammar) != 0) {
    cerr << "Unable to parse grammar:" << parser.error_message() << endl;
    return EXIT_FAILURE;
  }

  Memory memory;
  parserMemoryAddress = &memory;

  ErrorListener errorListener;
  errorListenerAdress = &errorListener;

  Lexer lexer;
  lexerAddress = &lexer;

  if (parser.parse(nextToken, syntaxError, alloc, NULL, &root,
                   &ambiguousInput)) {
    cerr << "Unable to parse input: " << parser.error_message() << endl;
    return EXIT_FAILURE;
  }

  Walker walker;
  walker.walk(root);

  return 0;
}
