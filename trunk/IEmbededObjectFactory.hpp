#ifndef I_EMBEDED_OBJECT_FACTORY_HPP__
#define I_EMBEDED_OBJECT_FACTORY_HPP__

#include	<string>

class IEmbededObjectFactory {
	public:
		virtual void *getObjectFromLibrary(std::string const & library) = 0;
		virtual ~IEmbededObjectFactory () {}
};

#endif
