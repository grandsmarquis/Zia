
#ifndef		__DAEMON_MANAGER_HH__
#define		__DAEMON_MANAGER_HH__

#include	<list>
#include	<map>
#include	<iostream>

#include	"Daemon.hpp"
#include	"Listener.hpp"
#include	"ConfigManager.hpp"
#include	"EmbededObjectFactory.hpp"
#include	"ModuleContainerList.hpp"
#include	"apiheaders/ModuleInfos.h"
#include	"apiheaders/Directives.h"
#include	"apiheaders/DirectivesOrder.h"

class DaemonManager {
public:
  void addPort(int port);
  void removePort(int port);
  bool isListeningOn(int port);
  int getNbDaemon() const;
  void update();
  void loadConf(ConfigManager const &cfg);
  void addModule(std::string const &name);
  void unloadConf(void);
  void breakDaemons(void);
  ~DaemonManager();
  DaemonManager();

private:
  std::list<Daemon *>		_dList;
  std::map<int, Listener *>	_port;
  ModuleContainerList		*_modules;
  bool _loaded;
  int _dPort;
  net::ISocket *_daemon;

  void dealDaemon(void);
};

#endif
