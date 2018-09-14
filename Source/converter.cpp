// -- Imports ------------------------------------------------------------------

#include <iostream>
#include <stdlib.h>

#include <yaep.h>

#include "converter.hpp"
#include "error_listener.hpp"
#include "lexer.hpp"
#include "memory.hpp"
#include "walker.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::string;

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

// -- Class --------------------------------------------------------------------

int Converter::parse() {
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

  return EXIT_SUCCESS;
}
