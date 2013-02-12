//
//  Socket.h
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__Net__Socket__
#define __Zia__Net__Socket__

#include "unistd.h"
#include <iostream>
#include <string>

#include <sys/socket.h>

namespace Net {
    class Socket {
    protected:
        int _fd;
        
    public:
        Socket(int scoket);
        Socket(int domain, int type, int protocol);
        ~Socket();
        
        void Listen(int backlog = 128);
        Socket * Accept();
        size_t Write(const void * data, size_t len);
        size_t Write(const std::string & str);
    };
}

#endif /* defined(__Zia__Net__Socket__) */
