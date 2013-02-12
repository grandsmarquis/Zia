//
//  Cond.cpp
//  Zia
//
//  Created by William Riancho on 11/02/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#include "Exception.h"
#include "Mutex.h"
#include "Cond.h"

namespace Thread {
    Cond::Cond() {
        if (0 != pthread_cond_init(&_cond, NULL))
        {
            throw Exception("cond init failed");
        }
    }
    
    Cond::~Cond() {
        
    }
    
    void Cond::Wait() {
        if (0 != pthread_cond_wait(&_cond, _mutex.getMutex()))
        {
            throw Exception("cond wait failed");
        }
    }
    
    void Cond::TimedWait(const struct timespec * _time)
    {
        if (0 != pthread_cond_timedwait(&_cond, _mutex.getMutex(), _time))
        {
            throw Exception("cond timedwait failed");
        }
    }
    
    void Cond::Signal() {
        if (0 != pthread_cond_signal(&_cond))
        {
            throw Exception("cond signal failed");
        }
    }
}