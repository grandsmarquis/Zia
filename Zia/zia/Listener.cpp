//
//  Listener.cpp
//  Zia
//
//  Created by William Riancho on 12/02/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#include "../net/TCPSocket.h"
#include "Listener.h"

Listener::Listener(int port) : /*_thread(*this),*/ _port(port){
  (*this)();
}

Listener::~Listener() {
  
}

void Listener::operator()() {
  Net::TCPSocket _sock(_port);
  Net::Socket * s;
  
  _sock.Listen();
    // for (;;) {
  s =_sock.Accept();
    // _worker.addConnexion();
    // }
}

void Listener::join() {
    // _thread.join();
}