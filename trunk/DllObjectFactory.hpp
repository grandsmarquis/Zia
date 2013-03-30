#ifndef DLL_OBJECT_FACTORY_HPP__
#define DLL_OBJECT_FACTORY_HPP__


#include <windows.h>

#include <string>
#include <map>

#include "IEmbededObjectFactory.hpp"

class DllObjectFactory : public IEmbededObjectFactory {
  private:
    std::map<std::string, HMODULE> _map;
    typedef void *(*bridge_func) ();

  public:
    DllObjectFactory();
    ~DllObjectFactory();

    void *getObjectFromLibrary(std::string const & library);
};

#endif
