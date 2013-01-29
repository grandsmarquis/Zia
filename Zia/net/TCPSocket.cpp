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

void print_ip_addr(const struct sockaddr_in * sinptr) {
    printf(
            "%d.%d.%d.%d",
			(ntohl(sinptr->sin_addr.s_addr) & 0xff000000) >> 24,
			(ntohl(sinptr->sin_addr.s_addr) & 0x00ff0000) >> 16,
			(ntohl(sinptr->sin_addr.s_addr) & 0x0000ff00) >>  8,
			(ntohl(sinptr->sin_addr.s_addr) & 0x000000ff));
}

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
    
    void TCPSocket::Listen(int backlog) {
        if (-1 == listen(_fd, backlog)) {
            throw Net::Exception(std::string("listen: ").append(strerror(errno)));
        }
    }
    
    void TCPSocket::Accept() {
        fd_set in_set;
        struct sockaddr accept_sockaddr;
        //IPV6 struct sockaddr_in6 accept_sockaddr;
        socklen_t address_len;
        int s, in_sock;
        
        bzero(&accept_sockaddr, sizeof(accept_sockaddr));
        address_len = sizeof(accept_sockaddr);
        
        FD_ZERO(&in_set);
        FD_SET(_fd, &in_set);

        s = select(_fd + 1, &in_set, NULL, NULL, NULL);
        if (-1 == s) {
            throw Net::Exception(std::string("select: ").append(strerror(errno)));
        }
        if (s == 1) {
            if (-1 == accept(_fd, (struct sockaddr *) &accept_sockaddr, &address_len)) {
                throw Net::Exception(std::string("accept: ").append(strerror(errno)));
            }
            if (AF_INET == accept_sockaddr.sa_family) {
                print_ip_addr((struct sockaddr_in *) &accept_sockaddr);
            } 
             /* IPV6
             else  if (AF_INET6 == accept_sockaddr.sin6_family) {
                char s[INET6_ADDRSTRLEN];
                inet_ntop(AF_INET6,
                          &(accept_sockaddr.sin6_addr),
                          s, INET6_ADDRSTRLEN);
                int i = 0;
                while(i < INET6_ADDRSTRLEN) {
                    printf("%x::", s[i]);
                    ++i;
                }
            } 
             */
             else {
                std::cout << "UNKNOW" << std::endl;
            }   
            std::cout << std::endl;
        }
    }
}
