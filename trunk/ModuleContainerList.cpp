
#include "ModuleContainerList.hpp"

ModuleContainerList::ModuleContainerList(std::string const &path, std::list<std::string> const &mlist)
  :_path(path), _factory(path)
{
  std::list<std::string>::const_iterator citer;
  for (citer = mlist.begin(); citer != mlist.end(); ++citer)
    {
      ModuleContainer *t = new ModuleContainer(_factory, *citer); 
      _list.push_front(t);
    }
}

EmbededObjectFactory const &ModuleContainerList::getFactory() const
{
  return (_factory);
}

std::string const &ModuleContainerList::getPath() const
{
  return (_path);
}

ModuleContainerList::~ModuleContainerList()
{
}

std::list<ModuleContainer *> const &ModuleContainerList::getList() const
{
  return (_list);
} 
