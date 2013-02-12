//
//  TCPSocket.h
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__TCPSocket__
#define __Zia__TCPSocket__

#include "Socket.h"

namespace Net {
    class TCPSocket : public Net::Socket {
        
    public:
        TCPSocket(int port);
    };
}

#endif /* defined(__Zia__TCPSocket__) */
