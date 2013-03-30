#ifndef EMBEDED_OBJECT_FACTORY_HPP__
#define EMBEDED_OBJECT_FACTORY_HPP__


#include "IEmbededObjectFactory.hpp"

#ifdef __unix__

#include "SoObjectFactory.hpp"

#elif defined _WIN32

#include <windows.h>

#include "DllObjectFactory.hpp"

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

    ~EmbededObjectFactory() {

    }

    template<typename T>
      T *getObjectFromLibrary(std::string const & library) {
        return static_cast<T *>(this->_factory->getObjectFromLibrary(this->_path + library));
      }
};

#endif

