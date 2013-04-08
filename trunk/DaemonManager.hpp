
#ifndef		__DAEMON_MANAGER_HH__
#define		__DAEMON_MANAGER_HH__

#include	<list>
#include	<map>
#include	<iostream>

#include	"Daemon.hpp"
#include	"Listener.hpp"
#include	"ConfigManager.hpp"
#include	"EmbededObjectFactory.hpp"

#include "apiheaders/ModuleInfos.h"
#include "apiheaders/Directives.h"
#include "apiheaders/DirectivesOrder.h"

class DaemonManager {

public:
  void addPort(int port);
  void removePort(int port);
  bool isListeningOn(int port);
  int getNbDaemon() const;
  void update();
  void loadConf(ConfigManager const &cfg);
  int getNbModules() const;
  std::map<ModuleInfos *, Directives *> const &getModules() const;
  void addModule(std::string const &name);

private:
  std::list<Daemon *>		_dList;
  std::map<ModuleInfos *, Directives *> _mList;
  std::map<int, Listener *>	_port;
};

#endif
