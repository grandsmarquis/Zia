#ifndef EVENT_CALLBACK_HPP
#define EVENT_CALLBACK_HPP 1

namespace Event {

  class Callback {
    public:
      Callback();
      ~Callback();
      void operator()();
  };

};

#endif
