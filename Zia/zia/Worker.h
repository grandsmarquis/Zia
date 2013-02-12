//
//  Worker.h
//  Zia
//
//  Created by William Riancho on 12/02/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__Worker__
#define __Zia__Worker__

#include <iostream>
#include <list>

#include "../event/Callback.h"
#include "../thread/Mutex.h"
#include "../thread/Cond.h"
#include "../my_module/MyModule.h"

class Worker : public Event::Callback {
private:
    // Thread::Thread _thread;
  std::list<Net::Socket *> _connexionWaiting;
  Thread::Mutex _connexionWaintingMutex;
  Thread::Cond _connexionWaitingCond;
  std::list<CrossModulePackage *> _connexion;
  MyModule _module;
  
public:
  Worker();
  
  virtual ~Worker();
  
  virtual void operator()();
  void addConnexion(Net::Socket * _sock);
};

#endif /* defined(__Zia__Worker__) */
