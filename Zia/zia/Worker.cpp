//
//  Worker.cpp
//  Zia
//
//  Created by William Riancho on 12/02/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#include "Worker.h"

Worker::Worker() : /* _thread(*this), */ _module(42) {
  
}

Worker::~Worker()
{
}

void Worker::operator()()
{
  CrossModulePackage *pkg;
  
  for (;;)
  {
    _connexionWaintingMutex.Lock();
    while (!_connexionWaiting.empty())
    {
      pkg = new CrossModulePackage(_connexionWaiting.back());
      _module.initPackage(*pkg);
      _connexion.push_back(pkg);
      _connexionWaiting.pop_back();
    }
    _connexionWaintingMutex.Unlock();
    
    if (_connexion.empty())
    {
      std::cout << "wait" << std::endl;
      _connexionWaitingCond.Wait();
      std::cout << "new connection" << std::endl;
    }
    else
    {
      for (std::list<CrossModulePackage *>::iterator it = _connexion.begin();
           it != _connexion.end(); ++it)
      {
        _module.yield(*(*it));
      }
    }
  }
}

void Worker::addConnexion(Net::Socket * _sock) {
  
  /*
   _connexionWaintingMutex.Lock();
   _connexionWaiting.push_back(_sock);
   _connexionWaintingMutex.Unlock();
   _connexionWaitingCond.Signal();
   */
  CrossModulePackage *pkg;
  
  pkg = new CrossModulePackage(_sock);
  for (;;) {
    _module.yield(*pkg);
  }
}

