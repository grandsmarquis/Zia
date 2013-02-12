//
//  Cond.h
//  Zia
//
//  Created by William Riancho on 11/02/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__Thread_Cond__
#define __Zia__Thread_Cond__

#include <iostream>

namespace Thread {
    class Cond {
    private:
        pthread_cond_t _cond;
        Mutex _mutex;
        
    public:
        Cond();
        ~Cond();
        void Wait();
        void TimedWait(const struct timespec * _time);
        void Signal();
    };
}

#endif /* defined(__Zia__Cond__) */
