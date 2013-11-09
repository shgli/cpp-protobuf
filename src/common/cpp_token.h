#ifndef _CPP_TOKEN_H
#define _CPP_TOKEN_H
#include <string>
#include <vector>


struct cxx_token
{
  cxx_token (location_t l,
             unsigned int t,
             std::string const& lt = std::string (),
             tree n = 0)
      : loc (l), type (t), literal (lt), node (n) {}

  location_t loc;      // Location of this token.
  unsigned int type;   // Untyped cpp_ttype.
  std::string literal; // Only used for name, keyword, string, amd number.
  tree node;           // Tree node for the number. The number can be
                       // represented as either literal, tree node, or
                       // both, depending on which lexer was used.
};

typedef std::vector<cxx_token> cxx_tokens;


#endif

