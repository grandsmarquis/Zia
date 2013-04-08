
#include "ModuleContainerList.hpp"

ModuleContainerList::ModuleContainerList(std::string const &path, std::list<std::string> const &mlist)
{
  std::list<std::string>::const_iterator citer;
  EmbededObjectFactory objectFactory(path);
  for (citer = mlist.begin(); citer != mlist.end(); ++citer)
    {
      _list.push_front(new ModuleContainer(objectFactory, *citer));
    }
}
