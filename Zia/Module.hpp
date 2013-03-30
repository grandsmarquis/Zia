#ifndef __MODULE_HPP__
#define __MODULE_HPP__ 1

#include "Directives.hpp"

class Module {
  public:
    virtual void assignDirectives(Directives *) = 0;
    virtual Directives *getDirectives() = 0;
    virtual ModuleInfos *getModuleInformations() = 0;
    virtual bool hasDirective(DirectivesOrder) = 0;
    virtual void init() = 0;
    virtual bool isLoaded() = 0;
    virtual void loadModule() = 0;
    virtual void unloadModule() = 0;
};

#endif
