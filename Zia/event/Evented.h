//
//  Evented.h
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__Evented__
#define __Zia__Evented__

#include "Evented.h"

#include <iostream>
#include <map>
#include <list>

#include "Callback.h"

namespace Event {
    
    template <typename T>
    class Evented {
    private:
        std::map<T, std::list<Event::Callback *> > _events;
        
    public:
        Evented() {
            
        }
        
        ~Evented() {
            
        }
        
        void on(T event, Callback * callback) {
            this->_events[event].push_back(callback);
        }
        
        void emit(T event) {
            std::list<Event::Callback *> & list = this->_events[event];
            std::list<Event::Callback *>::iterator it = list.begin();
            
            while (it != list.end()) {
                (*(*it))();
                ++it;
            }
            
        }
    };
    
};

#endif /* defined(__Zia__Evented__) */
