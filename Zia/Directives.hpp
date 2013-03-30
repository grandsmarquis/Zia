#ifndef __DIRECTIVES_HPP__
#define __DIRECTIVES_HPP__ 1

#include "DirectivesOrder.h"

class Directives {
  public:
    virtual void callDirective(DirectivesOrder, Request &) = 0;
    virtual void callDirective(DirectivesOrder, Response &) = 0;
    virtual void init() = 0;
};

#endif
