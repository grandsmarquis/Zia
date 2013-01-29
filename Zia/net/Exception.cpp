//
//  Exception.cpp
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#include "Exception.h"

namespace Net {

  Exception::Exception(std::string const & what) : _what(what) {}
  Exception::~Exception() {}
  const char * Exception::what() {
    return _what.c_str();
  }
}
