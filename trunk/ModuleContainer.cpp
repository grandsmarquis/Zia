#include "ModuleContainer.hpp"

ModuleContainer::ModuleContainer(EmbededObjectFactory &objectFactory, std::string const &name)
{
  _infos = objectFactory.getModuleInfos(name);
  _directives  = objectFactory.getModuleDirectives(name);
  if (!_infos && !_directives)
    {
      _loaded = false;
      std::cerr << "Unable to load module from: " << name << "." << std::endl;
    }
  else
    {
      _loaded = true;
      // _directives->init();
    }
}


bool ModuleContainer::isLoaded(void) const
{
  return (_loaded);
}

ModuleContainer::~ModuleContainer()
{
  if (_infos)
    delete(_infos);
  if (_directives)
    delete(_directives);
}
