//
//  TCPSocket.cpp
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>

#include <errno.h>
#include <strings.h>

#include "Exception.h"
#include "TCPSocket.h"

namespace Net {
    
    TCPSocket::TCPSocket(int port) : Socket(AF_INET, SOCK_STREAM, 0) {
        struct sockaddr_in sock_addr;
        
        bzero(&sock_addr, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        sock_addr.sin_port = htons(port);
    
        /* IPV6
         TCPSocket::TCPSocket(int port) : Socket(AF_INET6, SOCK_STREAM, 0) {
        
         struct sockaddr_in6 sock_addr;
        
         bzero(&sock_addr, sizeof(sock_addr));
         sock_addr.sin6_len = sizeof(sock_addr);
         sock_addr.sin6_family = AF_INET6;
         sock_addr.sin6_addr = in6addr_any;
         sock_addr.sin6_port = htons(port);
        */
        
        if (-1 == bind(_fd, (struct sockaddr *) &sock_addr, sizeof(sock_addr))) {
            throw Net::Exception(std::string("bind: ").append(strerror(errno)));
        }
    }
}
