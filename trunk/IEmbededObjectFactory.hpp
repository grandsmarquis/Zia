#ifndef I_EMBEDED_OBJECT_FACTORY_HPP__
#define I_EMBEDED_OBJECT_FACTORY_HPP__

#include	<string>

#include "apiheaders/ModuleInfos.h"
#include "apiheaders/Directives.h"

class IEmbededObjectFactory {
	public:
    // virtual void *getObjectFromLibrary(std::string const & library, std::string const & constructor);
    virtual ModuleInfos *getModuleInfos(std::string const & library) = 0;
    virtual Directives *getModuleDirectives(std::string const & library) = 0;
		virtual ~IEmbededObjectFactory () {}
};

#endif
