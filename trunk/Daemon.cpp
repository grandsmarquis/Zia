
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
  else
    {
      this->_running = false;
      if (!_b.isEmpty())
	{
	  Request *req = new Request(_b.getData(), _b.getSize());
	  _reqs.push_front(req);
	}
    }
}

void Daemon::work()
{
  std::cout << "CONNECTION_INIT" << std::endl;
  while (this->_running)
    {
      this->ReceiveAll();
      if (!_reqs.empty())
	{
	  std::list<Request *>::iterator iter;
	  for (iter = _reqs.begin(); iter != _reqs.end(); ++iter)
	    {
	      (*iter)->separate();
	      Response resp(NULL, 0);
	      std::cout << (*iter)->getHeader().getArg() << " " << _modules << std::endl;
	      call(PREPROCESS_REQUEST, *(*iter), resp);
	    }
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
  std::list<ModuleContainer *>::iterator iter;

  for (iter = _modules->_list.begin(); iter != _modules->_list.end(); ++iter)
    {
      (*iter)->_directives->callDirective(directiveorder, req, resp);
    }
}
