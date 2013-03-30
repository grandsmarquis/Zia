
#ifndef __DAEMON_HH__
#define __DAEMON_HH__

#include <iostream>
#include <string>

#include "ISocket.hh"
#include "IThread.hpp"

#include "Bucket.hpp"

#ifdef __unix__
	#include "ThreadUnix.hpp"
#else
	#include "ThreadWindows.hpp"
#endif

class Daemon {

public:
  Daemon(net::ISocket *socket, int port);
  void work(void);
  bool isRunning() const;
  void stop();

private:
  net::ISocket		*_socket;
  int			_port;
  IThread		*_thread;
  bool			_running;
  Bucket		_b;

  void ReceiveAll();
};

#endif
