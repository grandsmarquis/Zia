//
//  Exception.cpp
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#include "exception.h"

namespace Net {

  exception::exception(std::string const & what) : _what(what) {}
  exception::~exception() {}
  const char * exception::what() {
    return _what.c_str();
  }
}
