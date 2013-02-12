//
//  Socket.cpp
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>
#include "Socket.h"
#include "Exception.h"

void print_ip_addr(const struct sockaddr_in * sinptr) {
    printf(
           "%d.%d.%d.%d",
           (ntohl(sinptr->sin_addr.s_addr) & 0xff000000) >> 24,
           (ntohl(sinptr->sin_addr.s_addr) & 0x00ff0000) >> 16,
           (ntohl(sinptr->sin_addr.s_addr) & 0x0000ff00) >>  8,
           (ntohl(sinptr->sin_addr.s_addr) & 0x000000ff));
}

namespace Net {
    
    Socket::Socket(int socket) : _fd(socket) {}
    
    Socket::Socket(int domain, int type, int protocol) {
        _fd = socket(domain, type, protocol);
        if (-1 == _fd) {
            throw ;
        }
    }
    
    Socket::~Socket() {
        close(_fd);
    }
    
    
    void Socket::Listen(int backlog) {
        if (-1 == listen(_fd, backlog)) {
            throw Net::Exception(std::string("listen: ").append(strerror(errno)));
        }
    }
    
    Socket * Socket::Accept() {
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
        if (0 > s) {
            throw Net::Exception(std::string("select: ").append(strerror(errno)));
        }
        in_sock = accept(_fd, (struct sockaddr *) &accept_sockaddr, &address_len);
        if (0 > in_sock) {
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
        
        int yes = 1;
        socklen_t yes_length = sizeof(yes);
        
        setsockopt(in_sock, SOL_SOCKET, SO_KEEPALIVE, &yes, yes_length);
        
        return new Socket(in_sock);
    }
    
    size_t Socket::Write(const void * data, size_t len)
    {
        fd_set set;
        int rt, error = 0;
        size_t r;
        socklen_t length = sizeof(error);
        
        int yes = 1;
        socklen_t yes_length = sizeof(yes);
        
        getsockopt(_fd, SOL_SOCKET, SO_KEEPALIVE, &yes, &yes_length);
        
        std::cout << "Keep alive = " << yes << std::endl;
        
        rt = getsockopt(_fd, SOL_SOCKET, SO_ERROR, &error, &length);
        if (rt != 0)
        {
            std::cout << "disconnected" << std::endl;
            return 0;
        }
        else
        {
         
            std::cout << "connected" << std::endl;
         
            FD_ZERO(&set);
            FD_SET(_fd, &set);
            struct timeval tv = {3, 0};
            rt = select(_fd + 1, NULL, &set, NULL, &tv);
            if (0 > rt)
            {
                std::cout << "select failed" << std::endl;
                return 0;
            }
            else
            {
                // std::cout << "ok" << std::endl;
                // return write(_fd, data, len);
          
                r = send(_fd, data, len, 0);
                if (-1 == r)
                {
                    throw Exception(std::string("send fail: ").append(strerror(errno)));
                }
                return r;
            }
        }
    }
    
    size_t Socket::Write(const std::string & str)
    {
        return Write(str.c_str(), str.size());
    }
}