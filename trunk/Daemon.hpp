
#ifndef __DAEMON_HH__
#define __DAEMON_HH__

#include <iostream>
#include <string>
#include <list>
#include <queue>

#include "ISocket.hh"
#include "IThread.hpp"
#include "ModuleContainerList.hpp"
#include "Bucket.hpp"
#include "Request.h"
#include "Directives.h"

#ifdef __unix__
	#include "ThreadUnix.hpp"
#else
	#include "ThreadWindows.hpp"
#endif

#ifdef __unix__
	#include"MutexUnix.hpp"
#elif defined _WIN32
	#include"MutexCSWindows.hpp"
#endif


class DaemonManager;
class ModuleContainerList;

class Daemon {

public:
  Daemon(DaemonManager *man, net::ISocket *socket, int port, ModuleContainerList *_module);
  void work(void);
  bool isRunning() const;
  void stop();
  void call(DirectivesOrder directiveorder, Request &req, Response &resp, t_socket socket, sockaddr_in connexionInfos);
  ~Daemon();
  void setRunning(bool r);

private:
  net::ISocket		*_socket;
  int			_port;
  IThread		*_thread;
  bool			_running;
  Bucket		_b;
  DaemonManager		*_man;
  std::queue<Request *>	_reqs;
  ModuleContainerList	*_modules;
  IMutex                *_mutex;

  bool ReceiveAll();
};

#endif
