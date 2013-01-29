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
    class exception /* : public std::exception */{
    private:
        std::string _what;
        
    public:
        exception(std::string const & what);
        virtual ~exception();
        virtual const char * what();
    };
}

#endif /* defined(__Zia__Exception__) */
