//
//  Listener.h
//  Zia
//
//  Created by William Riancho on 12/02/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__Listener__
#define __Zia__Listener__

#include "../zia/Worker.h"

class Listener : public Event::Callback {
private:
    // Thread::Thread _thread;
  int _port;
  Worker _worker;
  
public:
  Listener(int port);
  ~Listener();
  void operator()();
  void join();
  
};

#endif /* defined(__Zia__Listener__) */