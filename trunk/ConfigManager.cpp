
#include "ConfigManager.hpp"

ConfigManager::ConfigManager(std::string const &name)
{
  libconfig::Config cfg;

  try
    {
      cfg.readFile(name.c_str());
    }
  catch(const libconfig::FileIOException &fioex)
    {
      std::cerr << "I/O error while reading file." << std::endl;
      return;
    }
  catch(const libconfig::ParseException &pex)
    {
      std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
		<< " - " << pex.getError() << std::endl;
      return;
    }
  parse(cfg.getRoot());
}

void ConfigManager::parse(const libconfig::Setting &root)
{
  if (root.exists("ports"))
    {
      const libconfig::Setting &ports = root["ports"];
      if (ports.isArray())
	{
	  int count = ports.getLength();
	  for (int i = 0; i < count; ++i)
	    {
	      const libconfig::Setting &port = ports[i];
	      if (port.isNumber())
		{
		  _ports.push_front(port);
		}
	    }
	}
    }
  if (root.exists("modules"))
    {
      const libconfig::Setting &modules = root["modules"];
      if (modules.isArray())
	{
	  int count = modules.getLength();
	  for (int i = 0; i < count; ++i)
	    {
	      const libconfig::Setting &module = modules[i];
	      if (module.isScalar())
		{
		  _modules.push_front(module);
		}
	    }
	}
    }
}

std::list<std::string> const &ConfigManager::getModules(void) const
{
  return (_modules);
}

std::list<int> const &ConfigManager::getPorts(void) const
{
  return (_ports);
}
