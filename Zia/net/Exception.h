//
//  Exception.h
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__Exception__
#define __Zia__Exception__

#include <exception>
#include <string>

namespace Net {
    class Exception : public std::exception {
    private:
        std::string _what;
        
    public:
        Exception(std::string const & what) : _what(what) {}
        virtual ~Exception() {}
        virtual const char * what() {
            return _what.c_str();
        }
    };
}

#endif /* defined(__Zia__Exception__) */
