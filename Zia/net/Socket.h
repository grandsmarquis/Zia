//
//  Socket.h
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__Net__Socket__
#define __Zia__Net__Socket__

#include <iostream>

#include <sys/socket.h>

namespace Net {
    class Socket {
    protected:
        int _fd;
        
    public:
        Socket(int domain, int type, int protocol);
        ~Socket();
    };
}

#endif /* defined(__Zia__Net__Socket__) */
