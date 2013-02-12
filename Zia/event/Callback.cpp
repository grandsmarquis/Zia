//
//  Callback.cpp
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

#include <strings.h>


#include "../net/TCPSocket.h"
#include "Callback.h"

#include <iostream>



namespace Event {
    
    Callback::Callback() {
        
    }
    
    Callback::~Callback() {
        
    }
    /*
    void Callback::operator()() {
        Net::TCPSocket sock(8888);
     
         listen(sock, 128);
         
         FD_ZERO(&in_set);
         FD_SET(sock, &in_set);
         s = select(sock + 1, &in_set, NULL, NULL, NULL);
         if (s == 1) {
         in_sock = accept(sock, &accept_sockaddr, &address_len);
         }
         write(in_sock, "Hello world", strlen("hello world"));
     
    }
     */
    
    void *Callback::simpleSymbole(void *self) {
        Event::Callback *cb;
        
        cb = reinterpret_cast<Event::Callback *>(self);
        (*cb)();
        return NULL;
    }
    
}