#ifndef SO_OBJECT_FACTORY_HPP__
#define SO_OBJECT_FACTORY_HPP__

#include <map>
#include <string>

#include "IEmbededObjectFactory.hpp"

class SoObjectFactory : public IEmbededObjectFactory {
  private:
    std::map<std::string, void *> _map;
    typedef void *(*bridge_func)();

  public:
    SoObjectFactory();
    ~SoObjectFactory();

    void *getObjectFromLibrary(std::string const & library);
};

#endif
