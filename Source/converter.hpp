#include <functional>
#include <iostream>

#include "objstack.h"
#include <yaep.h>

#include "error_listener.hpp"
#include "lexer.hpp"
#include "memory.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::string;

static ErrorListener *errorListenerAdress;
static Lexer *lexerAddress;
static Memory *parserMemoryAddress;

int nextToken(void **attribute) { return lexerAddress->nextToken(attribute); }

void syntaxError(int errorToken, void *errorTokenData, int ignoredToken,
                 void *ignoredTokenData, int recoveredToken,
                 void *recoveredTokenData) {
  return errorListenerAdress->syntaxError(errorToken, errorTokenData,
                                          ignoredToken, ignoredTokenData,
                                          recoveredToken, recoveredTokenData);
}

void *alloc(int size) { return parserMemoryAddress->allocate(size); }

class Converter {

  const char *grammar = "\n"
                        "TERM\n"
                        "NUMBER = 49;\n"
                        "START : NUMBER # 0\n"
                        "      ;\n";

  static string toString(yaep_tree_node *node) {
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

public:
  int parse() {
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

    cout << "Type of top node: " << toString(root) << endl;
    cout << "Code of top node: " << (root->val).term.code << endl;

    return EXIT_SUCCESS;
  }
};
