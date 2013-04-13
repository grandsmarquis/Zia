#ifndef DLL_OBJECT_FACTORY_HPP__
#define DLL_OBJECT_FACTORY_HPP__

#define _WINSOCKAPI_
#include <windows.h>

#include <string>
#include <map>

#include "IEmbededObjectFactory.hpp"

class DllObjectFactory : public IEmbededObjectFactory {
private:
  std::map<std::string, HMODULE> _map;
  typedef void *(*bridge_func) ();
  typedef ModuleInfos *(*module_infos_bridge_func)();
  typedef Directives *(*directives_bridge_func)();
  
  
  HMODULE getObjectFromLibrary(std::string const & library);

  
  
public:
  DllObjectFactory();
  ~DllObjectFactory();

  virtual ModuleInfos *getModuleInfos(std::string const & library);
  virtual Directives *getModuleDirectives(std::string const & library);
  
};

#endif
