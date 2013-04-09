
#include "ModuleContainerList.hpp"

ModuleContainerList::ModuleContainerList(std::string const &path, std::list<std::string> const &mlist)
  :_path(path), _factory(path),
#ifdef __unix__
   _mutex(new MutexUnix())
#elif defined _WIN32
   _mutex(new MutexCSWindows())
#endif
{
  _att = 0;
  _mutex->MutexInit();
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
  std::cout << "Module list was deleted" << std::endl;
}

std::list<ModuleContainer *> const &ModuleContainerList::getList() const
{
  return (_list);
} 

void ModuleContainerList::attach()
{
  _mutex->MutexLock();
  _att++;
  _mutex->MutexUnlock();
}

void ModuleContainerList::detach()
{
  _mutex->MutexLock();
  _att--;
  _mutex->MutexUnlock();
}

bool ModuleContainerList::isAttached() const
{
    _mutex->MutexLock();
    int tmp = _att;
    _mutex->MutexUnlock();
    return (tmp != 0);
}
