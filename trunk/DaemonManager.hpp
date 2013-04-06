
#ifndef		__DAEMON_MANAGER_HH__
#define		__DAEMON_MANAGER_HH__

#include	<list>
#include	<map>
#include	<iostream>

#include	"Daemon.hpp"
#include	"Listener.hpp"
#include	"ConfigManager.hpp"

class DaemonManager {

public:
  void addPort(int port);
  void removePort(int port);
  bool isListeningOn(int port);
  int getNbDaemon() const;
  void update();
  void loadConf(ConfigManager const &cfg);

private:
  std::list<Daemon *>	_dList;
  std::map<int, Listener *>	_port;
};

#endif
