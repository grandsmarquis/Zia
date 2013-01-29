//
//  Socket.cpp
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#include <unistd.h>
#include "Socket.h"

namespace Net {
    
    Socket::Socket(int domain, int type, int protocol) {
        _fd = socket(domain, type, protocol);
        if (-1 == _fd) {
            throw ;
        }
    }
    
    Socket::~Socket() {
        close(_fd);
    }
}