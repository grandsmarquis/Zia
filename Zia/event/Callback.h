//
//  Callback.h
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__Callback__
#define __Zia__Callback__

namespace Event {
    
    class Callback {
    public:
        Callback();
        ~Callback();
        void operator()();
        static void *simpleSymbole(void *self);
    };
    
};

#endif /* defined(__Zia__Callback__) */
