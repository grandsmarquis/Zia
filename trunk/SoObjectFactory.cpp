
#include <map>
#include <iostream>
#include <string>

#include <dlfcn.h>

#include "SoObjectFactory.hpp"

SoObjectFactory::SoObjectFactory() {

}

SoObjectFactory::~SoObjectFactory() {

}

void *SoObjectFactory::getObjectFromLibrary(std::string const & library) {
  void *lib;

  if (!(lib = this->_map[library])) {
    lib = dlopen((library + ".so").c_str(), RTLD_LAZY | RTLD_LOCAL);
    if (lib == NULL) {
      std::cerr << dlerror() << std::endl;
      return NULL;
    }
    this->_map[library] = lib;
  }
  SoObjectFactory::bridge_func create_object = (SoObjectFactory::bridge_func) dlsym(lib, "create_object");
  return create_object();
}
