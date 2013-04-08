#ifndef __H_MODULECONTAINERLIST_HH_
#define __H_MODULECONTAINERLIST_HH_

#include <list>
#include <string>

#include "ModuleContainer.hpp"

class ModuleContainerList
{
public:
  ModuleContainerList(std::string const &path, std::list<std::string> const &mlist);
  EmbededObjectFactory const &getFactory() const;
  std::string const &getPath() const;
  ~ModuleContainerList();
  std::list<ModuleContainer *> const &getList() const;
private:
  std::string _path;
  EmbededObjectFactory _factory;
  std::list<ModuleContainer *> _list;
};


#endif
