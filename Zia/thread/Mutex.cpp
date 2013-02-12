//
//  Mutex.cpp
//  Zia
//
//  Created by William Riancho on 11/02/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#include <pthread.h>
#include <errno.h>

#include "Exception.h"
#include "Mutex.h"

namespace Thread
{
    Mutex::Mutex()
    {
        if (0 != pthread_mutex_init(&_mutex, NULL))
        {
            throw Thread::Exception("unable to init mutex");
        }
    }
        
    Mutex::~Mutex()
    {
    }
        
    void Mutex::Lock()
    {
        if (0 != pthread_mutex_lock(&_mutex))
        {
            throw Thread::Exception("mutex lock failed");
        }
    }

    bool Mutex::TryLock()
    {
        bool rt;
            
        switch (pthread_mutex_trylock(&_mutex))
        {
            case EBUSY:
                rt = false;
                break;
            case 0:
                rt = true;
            case EINVAL:
            default:
                throw Thread::Exception("Thread::Mutex::TryLock : invalid mutex");
                break;
        }
        return rt;
    }
    
    void Mutex::Unlock()
    {
        if (0 != pthread_mutex_unlock(&_mutex))
        {
            throw Exception("mutex unlock failed");
        }
    }
    
    pthread_mutex_t *Mutex::getMutex()
    {
        return &_mutex;
    }
}