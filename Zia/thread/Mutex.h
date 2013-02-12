//
//  Mutex.h
//  Zia
//
//  Created by William Riancho on 11/02/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__Thread_Mutex__
#define __Zia__Thread_Mutex__

#include <pthread.h>

namespace Thread {
    class Mutex {
    private:
        pthread_mutex_t _mutex;
    public:
        Mutex();
        ~Mutex();
        
        void Lock();
        bool TryLock();
        void Unlock();
        pthread_mutex_t *getMutex();
    };
}

#endif /* defined(__Zia__Mutex__) */
