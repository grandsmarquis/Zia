
#ifndef EVENTED_HPP
#define EVENTED_HPP

#include <iostream>
#include <map>
#include <list>

#include "Evented.hpp"
#include "Callback.hpp"

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

#endif
