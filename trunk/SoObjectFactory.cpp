
#include <map>
#include <iostream>
#include <string>

#include <dlfcn.h>

#include "apiheaders/ModuleInfos.h"
#include "SoObjectFactory.hpp"

SoObjectFactory::SoObjectFactory() {

}

SoObjectFactory::~SoObjectFactory() {
  std::map<std::string, void *>::iterator it = this->_map.begin();
  while (it != this->_map.end()) {
    dlclose(it->second);
    ++it;
  }
}

void *SoObjectFactory::loadLibrary(std::string const & library) {
  void *lib;

  if (!(lib = this->_map[library])) {
    lib = dlopen((library + ".so").c_str(), RTLD_LAZY | RTLD_LOCAL);
    if (lib == NULL) {
      std::cerr << dlerror() << std::endl;
      return NULL;
    }
    this->_map[library] = lib;
  }
  return lib;
}

ModuleInfos *SoObjectFactory::getModuleInfos(std::string const & library) {
  void *lib;

  if ((lib = this->loadLibrary(library))) {
    SoObjectFactory::module_infos_bridge_func create_object =
      (SoObjectFactory::module_infos_bridge_func) dlsym(lib, "get_module_infos");
    return create_object();
  } else {
    return NULL;
  }
}

Directives *SoObjectFactory::getModuleDirectives(std::string const & library) {
  void *lib;

  if ((lib = this->loadLibrary(library))) {
    SoObjectFactory::directives_bridge_func create_object =
      (SoObjectFactory::directives_bridge_func) dlsym(lib, "get_directives");
    return create_object();
  } else {
    return NULL;
  }
}
