
#ifndef _H_MODULE__H_
#define _H_MODULE__H_

#include <iostream>
#include <string>

#include "EmbededObjectFactory.hpp"

class ModuleContainer
{
public:
  ModuleContainer(EmbededObjectFactory &objectFactory, std::string const &name);
  bool isLoaded(void) const;
  ~ModuleContainer();

  ModuleInfos	*_infos;
  Directives	*_directives;

private:
  bool		_loaded;

};

#endif
