
#define _WINSOCKAPI_
#include <windows.h>
#include <iostream>
#include <string>
#include "DllObjectFactory.hpp"


DllObjectFactory::DllObjectFactory() {

}

DllObjectFactory::~DllObjectFactory() {
  std::map<std::string, HMODULE>::iterator it = this->_map.begin();
  while (it != this->_map.end()) {
    FreeLibrary(it->second);
    ++it;
  }
}

HMODULE DllObjectFactory::getObjectFromLibrary(std::string const & library) {
  HMODULE lib;

  if (!(lib = this->_map[library])) {
    lib = LoadLibrary((library + ".dll").c_str());
    if (NULL == lib) {
      std::cerr << "DLLObjectFactory: error loading " << library << std::endl;
      return NULL;
    }
    this->_map[library] = lib;
  }
  return (lib);
}

ModuleInfos *DllObjectFactory::getModuleInfos(std::string const & library) {
  HMODULE lib;
  
  lib = getObjectFromLibrary(library);
  if (lib)
    {
      DllObjectFactory::module_infos_bridge_func create_object = (DllObjectFactory::module_infos_bridge_func) GetProcAddress(lib, "get_module_infos");
      if (create_object)
	return (create_object());
      else
	return (NULL);
    }
  else
    return (NULL);
}

Directives *DllObjectFactory::getModuleDirectives(std::string const & library) {
  HMODULE lib;
  
  lib = getObjectFromLibrary(library);
  if (lib)
    {
      DllObjectFactory::directives_bridge_func create_object = (DllObjectFactory::directives_bridge_func) GetProcAddress(lib, "get_directives");
      if (create_object)
	return (create_object());
      else
	return (NULL);
    }
  else
    return (NULL);
}
