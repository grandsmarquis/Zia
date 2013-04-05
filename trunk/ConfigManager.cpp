
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
}

std::list<std::string> const &ConfigManager::getModuler(void) const
{
}
