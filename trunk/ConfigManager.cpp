
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
  setDefaults();
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
  if (root.exists("modulePath"))
    {
      const libconfig::Setting &path = root["modulePath"];
      if (path.isScalar())
	{
	  _path += path.c_str();
	}
    }
  if (root.exists("author"))
    {
      const libconfig::Setting &author = root["author"];
      if (author.isScalar())
	{
	  _author += author.c_str();
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

std::string const &ConfigManager::getModulePath(void) const
{
  return (_path);
}

std::string const &ConfigManager::getAuthor(void) const
{
  return (_author);
}

void ConfigManager::setDefaults(void)
{
  if (_ports.empty())
    {
      std::cerr << "No ports set after reading config. Setting defaults to 80 and 3030." << std::endl;
      _ports.push_front(80);
      _ports.push_front(3030);
    }
  if (_modules.empty())
    {
      std::cerr << "No modules set after reading config. Setting defaults to php and ssl." << std::endl;
      _modules.push_front("php");
    }
}
