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
