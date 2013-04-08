
#include "Request.h"
#include "Daemon.hpp"

#ifdef __unix__
	static void*                    daemonize(void* param)
#elif defined _WIN32
	DWORD WINAPI                    daemonize(void* param)
#endif
{
  Daemon*   daemon;
  daemon = reinterpret_cast<Daemon*>(param);
  daemon->work();
#ifdef __unix__
  return (NULL);
#elif defined _WIN32
  return (0);
#endif
}



Daemon::Daemon(DaemonManager *manager, net::ISocket *socket, int port, ModuleContainerList *list)
  : _socket(socket), _port(port), _running(true), _man(manager), _modules(list)
{
#ifdef __unix__
  this->_thread = new ThreadUnix();
#elif defined _WIN32
  this->_thread = new ThreadWindows();
#endif
  this->_thread->thread_create(this, daemonize);
}

void Daemon::ReceiveAll()
{
  std::string ss;
  char buffer[254];
  int rec;
  
  rec =_socket->Recieve(buffer, 254);
  if (rec > 0)
    {
      this->_b.pushData(buffer, rec);
    }
  if (this->_b.canCut())
    {
      char *data = _b.getData();
      Request *req = new Request(data, _b.getSize());
      _reqs.push(req);
    }
  if (rec <= 0)
    {
      this->_running = false;
    }
}

void Daemon::work()
{
  std::cout << "CONNECTION_INIT" << std::endl;
  while (this->_running)
    {
      this->ReceiveAll();
      Request *tmp;
      while (!_reqs.empty())
	{
	  tmp = _reqs.front();
	  tmp->separate();
	  Response resp(NULL, 0);
	  std::cout << "BEFORE :: " << tmp->getHeader().getCommand() << std::endl;
	  call(PREPROCESS_REQUEST, *(tmp), resp);
	  std::cout << "AFTER" << std::endl;
	  _reqs.pop();
	}
    }
  std::cout << "CONNECTION_CLOSED" << std::endl;
}

bool Daemon::isRunning() const
{
  return (this->_running);
}

void Daemon::stop()
{
  this->_running = false;
  this->_thread->thread_cancel();
}

void Daemon::call(DirectivesOrder directiveorder, Request &req, Response &resp)
{
  std::list<ModuleContainer *>::const_iterator iter;

  for (iter = _modules->getList().begin(); iter != _modules->getList().end(); ++iter)
    {
      //      (*iter)->_directives->callDirective(directiveorder, req, resp);
      (*iter)->_directives->init();
    }
}
