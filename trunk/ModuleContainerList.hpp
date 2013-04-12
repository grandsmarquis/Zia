#ifndef __H_MODULECONTAINERLIST_HH_
#define __H_MODULECONTAINERLIST_HH_

#include <list>
#include <string>
#ifdef __unix__

#include"MutexUnix.hpp"
#elif defined _WIN32
#include"MutexCSWindows.hpp"
#endif

#include "ModuleContainer.hpp"

class ModuleContainerList
{
public:
  ModuleContainerList(std::string const &path, std::list<std::string> const &mlist);
  EmbededObjectFactory const &getFactory() const;
  std::string const &getPath() const;
  ~ModuleContainerList();
  std::list<ModuleContainer *> const &getList() const;
  void attach();
  void detach();
  bool isAttached() const;

private:
  std::string		_path;
  EmbededObjectFactory _factory;
  std::list<ModuleContainer *> _list;
  int			_att;
  IMutex		*_mutex;

};


#endif
