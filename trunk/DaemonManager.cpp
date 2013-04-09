#include "DaemonManager.hpp"

DaemonManager::DaemonManager()
  :_loaded(false)
{
  
}

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
  (void) name;
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
    if (iter->second->shouldExist())
      {
	tmp = iter->second->getNewClient();
	if (tmp)
	  {
	    _dList.push_front(new Daemon(this, tmp, iter->first, _modules));
	  }
      }
  }
}

void DaemonManager::loadConf(ConfigManager const &cfg)
{
  
  std::list<int>::const_iterator iter;

  if (_loaded)
    unloadConf();
  for (iter = cfg.getPorts().begin(); iter != cfg.getPorts().end(); ++iter)
    {
      if (this->isListeningOn(*iter))
	{
	  _port[*iter]->setExistance(true);
	}
      else
	this->addPort(*iter);
    }
  _modules = new ModuleContainerList(cfg.getModulePath(), cfg.getModules());
  _modules->attach();
  _loaded = true;
}

void DaemonManager::unloadConf(void)
{
  std::map<int, Listener *>::iterator iter;

  for (iter = _port.begin(); iter != _port.end(); ++iter)
    {
      iter->second->setExistance(false);
    }
  _modules->detach();
  if (!_modules->isAttached())
    delete(_modules);
}

void DaemonManager::breakDaemons(void)
{

}

DaemonManager::~DaemonManager()
{
}
