#ifndef __H_MODULECONTAINERLIST_HH_
#define __H_MODULECONTAINERLIST_HH_

#include <list>
#include <string>

#include "ModuleContainer.hpp"

class ModuleContainerList
{
public:
  ModuleContainerList(std::string const &name, std::list<std::string> const &mlist);

  std::list<ModuleContainer *> _list;
private:

};


#endif
