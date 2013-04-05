
#ifndef __CONFIGMANAGER_HH__
#define __CONFIGMANAGER_HH__

#include <libconfig.h++>
#include <list>
#include <string>
#include <iostream>

class ConfigManager
{
public:
  ConfigManager(std::string const &name);
  std::list<std::string> const &getModuler(void) const;
  
private:
  std::list<std::string> _modules;
};

#endif
