//
//  Exception.h
//  Zia
//
//  Created by William Riancho on 11/02/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__Thread_Exception__
#define __Zia__Thread_Exception__

#include <string>

namespace Thread {
    class Exception /* : public std::exception */{
    private:
        std::string _what;
        
    public:
        Exception(std::string const & what);
        virtual ~Exception();
        virtual const char * what();
    };
}

#endif /* defined(__Zia__Thread_Exception__) */
