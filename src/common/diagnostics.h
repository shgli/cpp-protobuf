// file      : odb/diagnostics.hxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : GNU GPL v3; see accompanying LICENSE file

#ifndef _PROTOBUF_DIAGNOSTICS_HXX
#define _PROTOBUF_DIAGNOSTICS_HXX

#include <gcc-fwd.h>

#include <string>
#include <cstddef>
#include <iostream>

using std::endl;

std::ostream&
error (location_t);

std::ostream&
warn (location_t);

std::ostream&
info (location_t);

//
//
class cxx_lexer;

std::ostream&
error (cxx_lexer&);

std::ostream&
warn (cxx_lexer&);

std::ostream&
info (cxx_lexer&);

std::string
location_string (location_t, bool leaf = false);

// location_t macro wrappers.
//
std::string
location_file (location_t);

std::size_t
location_line (location_t);

std::size_t
location_column (location_t);

#endif // ODB_DIAGNOSTICS_HXX
