#include "DaemonManager.hpp"

DaemonManager::DaemonManager()
  :_loaded(false), _daemon(NULL)
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
	    if ((iter->first) == _dPort)
	      {
		std::cout << "Daemon connected!" << std::endl;
		if (_daemon)
		  {
		    std::cout << "Can just take one Daemon" << std::endl;
		    delete(tmp);
		  }
		else
		  {
		    _daemon = tmp;
		  }
	      }
	    else
	      {
		_dList.push_front(new Daemon(this, tmp, iter->first, _modules));
		cleanDList();
	      }
	  }
      }
  }
  dealDaemon();
}

void DaemonManager::cleanDList()
{
  std::list<Daemon *>::iterator iter;
  Daemon *tmp;

  for (iter = _dList.begin(); iter != _dList.end(); ++iter) {
    if ((*iter)->isRunning())
      {
      }
    else
      {
	tmp = *iter;
	_dList.erase(iter++);
	delete(tmp);
      }
  }

}

void DaemonManager::dealDaemon(void)
{
  char buffer[254];
  int rec;

  if (_daemon)
    {
      rec = _daemon->Recieve(buffer, 253);
      if (rec > 0)
	{
	  buffer[rec] = '\0';
	  std::cout << "Will load new conf : " << buffer << "." << std::endl;
 	  ConfigManager config(buffer);
	  loadConf(config);
	}
      else
	{
	  delete (_daemon);
	  _daemon = NULL;
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
  _dPort = cfg.getDPort();
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
