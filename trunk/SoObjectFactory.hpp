#ifndef SO_OBJECT_FACTORY_HPP__
#define SO_OBJECT_FACTORY_HPP__

#include <map>
#include <string>

#include "apiheaders/ModuleInfos.h"
#include "apiheaders/Directives.h"

#include "IEmbededObjectFactory.hpp"

class SoObjectFactory : public IEmbededObjectFactory {
  private:
    std::map<std::string, void *> _map;
    typedef void *(*bridge_func)();
    typedef ModuleInfos *(*module_infos_bridge_func)();
    typedef Directives *(*directives_bridge_func)();

    void *loadLibrary(std::string const & library);

  public:
    SoObjectFactory();
    virtual ~SoObjectFactory();

    virtual ModuleInfos *getModuleInfos(std::string const & library);
    virtual Directives *getModuleDirectives(std::string const & library);
};

#endif
