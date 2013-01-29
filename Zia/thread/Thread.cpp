//
//  Thread.cpp
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#include <pthread.h>
#include "Thread.h"

namespace Thread {
    Thread::Thread(Event::Callback & callback) {
        if (0 != pthread_create(&_thread, NULL, Event::Callback::simpleSymbole, reinterpret_cast<void *>(&callback))) {
            throw ;
        }
    }
    
    Thread::~Thread() {}

    void Thread::join() {
        if (0 != pthread_join(_thread, NULL)) {
            throw;
        }
    }
}
