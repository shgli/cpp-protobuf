// file      : odb/diagnostics.cxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : GNU GPL v3; see accompanying LICENSE file

#include <gcc.h>

#include <sstream>

#include <CppLexer.h>
#include <diagnostics.h>

using namespace std;

std::ostream&
error (location_t loc)
{
  errorcount++;
  cerr << LOCATION_FILE (loc) << ':'
       << LOCATION_LINE (loc) << ':'
       << LOCATION_COLUMN (loc) << ':'
       << " error: ";
  return cerr;
}

std::ostream&
warn (location_t loc)
{
  warningcount++;
  cerr << LOCATION_FILE (loc) << ':'
       << LOCATION_LINE (loc) << ':'
       << LOCATION_COLUMN (loc) << ':'
       << " warning: ";
  return cerr;
}

std::ostream&
info (location_t loc)
{
  cout << LOCATION_FILE (loc) << ':'
       << LOCATION_LINE (loc) << ':'
       << LOCATION_COLUMN (loc) << ':'
       << " info: ";
  return cerr;
}

std::ostream&
error (cxx_lexer& l)
{
  return error (l.location ());
}

std::ostream&
warn (cxx_lexer& l)
{
  return warn (l.location ());
}

std::ostream&
info (cxx_lexer& l)
{
  return info (l.location ());
}

std::string
location_string (location_t loc, bool leaf)
{
  ostringstream ostr;

  if (leaf)
    ostr << LOCATION_FILE (loc);
  else
    ostr << LOCATION_FILE (loc);

  ostr << ':' << LOCATION_LINE (loc) << ':' << LOCATION_COLUMN (loc);
  return ostr.str ();
}

std::string
location_file (location_t loc)
{
  return std::string(LOCATION_FILE (loc));
}

size_t
location_line (location_t loc)
{
  return LOCATION_LINE (loc);
}

size_t
location_column (location_t loc)
{
  return LOCATION_COLUMN (loc);
}
