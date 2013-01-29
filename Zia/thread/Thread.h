//
//  Thread.h
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__Thread__
#define __Zia__Thread__

#include <pthread.h>
#include "../event/Callback.h"

namespace Thread {
    class Thread {
    protected:
        pthread_t _thread;
    public:
        Thread(Event::Callback & callback);
        ~Thread();
        void join();
    };
}

#endif /* defined(__Zia__Thread__) */
