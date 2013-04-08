#include "DaemonManager.hpp"

void DaemonManager::addPort(int port)
{
  Listener *tmp;
  if (!isListeningOn(port))
    {
      tmp = new Listener(port);
      if (tmp->succeedBind())
	_port[port] = tmp;
      else
	{
	  delete (tmp);
	  std::cerr << "Can't listen on port : " << port << std::endl;
	}
    }
}

void DaemonManager::addModule(std::string const &name)
{
  EmbededObjectFactory objectFactory("../modules/");

  ModuleInfos *moduleInfos = objectFactory.getModuleInfos(name);
  Directives *moduleDirectives = objectFactory.getModuleDirectives(name);

  if (!moduleInfos || !moduleDirectives)
    std::cerr << "Unable to load module : " << name << "." << std::endl;

  //Check error and add to map

}

void DaemonManager::removePort(int port)
{
  if (isListeningOn(port))
    _port.erase(port);
}

bool DaemonManager::isListeningOn(int port)
{
  std::map<int, Listener *>::const_iterator it = _port.find(port);
  return (it != _port.end());
}

int DaemonManager::getNbDaemon() const
{
  return (_dList.size());
}

void DaemonManager::update()
{
  std::map<int, Listener *>::iterator iter;
  net::ISocket *tmp;


  for (iter = _port.begin(); iter != _port.end(); ++iter) {
    tmp = iter->second->getNewClient();

    if (tmp)
      _dList.push_front(new Daemon(tmp, iter->first));
  }
}

void DaemonManager::loadConf(ConfigManager const &cfg)
{
  std::list<int>::const_iterator iter;
  std::list<std::string>::const_iterator citer;
    
  for (iter = cfg.getPorts().begin(); iter != cfg.getPorts().end(); ++iter)
    {
      this->addPort(*iter);
    }
  for (citer = cfg.getModules().begin(); citer != cfg.getModules().end(); ++citer)
    {
      this->addModule(*citer);
    }
}

std::map<ModuleInfos *, Directives *> const &DaemonManager::getModules() const
{
  return (_mList);
}

int DaemonManager::getNbModules() const
{
  return (_mList.size());
}
