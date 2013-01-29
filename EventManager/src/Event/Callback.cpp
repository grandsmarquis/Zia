#include "Callback.hpp"

#include <iostream>

namespace Event {

  Callback::Callback() {

  }

  Callback::~Callback() {

  }

  void Callback::operator()() {
    std::cout << "Hello world" << std::endl;
  }

}
