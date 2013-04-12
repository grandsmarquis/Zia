#ifndef EMBEDED_OBJECT_FACTORY_HPP__
#define EMBEDED_OBJECT_FACTORY_HPP__


#include "apiheaders/Module.h"
#include "IEmbededObjectFactory.hpp"

#ifdef __unix__

#include "SoObjectFactory.hpp"

#elif defined _WIN32

#define _WINSOCKAPI_
#include <windows.h>

#include "DllObjectFactory.hpp"
#include "apiheaders/ModuleInfos.h"
#include "apiheaders/Directives.h"

#endif

#include <string>

class EmbededObjectFactory {
  private:
    std::string _path;
    IEmbededObjectFactory *_factory;
  public:

    EmbededObjectFactory(std::string const & path) : _path(path) {
#ifdef __unix__
      this->_factory = new SoObjectFactory();
#elif defined _WIN32
      this->_factory = new DllObjectFactory();
#endif
    }

    virtual ~EmbededObjectFactory() {
      delete this->_factory;
    }

    ModuleInfos *getModuleInfos(std::string const & library) {
      return static_cast<ModuleInfos *>(this->_factory->getModuleInfos(this->_path + library));
    }
    Directives *getModuleDirectives(std::string const & library) {
      return static_cast<Directives*>(this->_factory->getModuleDirectives(this->_path + library));
    }
};

#endif

