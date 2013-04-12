
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
  : _socket(socket), _port(port), _running(true), _man(manager), _modules(list),
#ifdef __unix__
    _mutex(new MutexUnix())
#elif defined _WIN32
    _mutex(new MutexCSWindows())
#endif

{
  _modules->attach();
  _mutex->MutexInit();
#ifdef __unix__
  this->_thread = new ThreadUnix();
#elif defined _WIN32
  this->_thread = new ThreadWindows();
#endif
  this->_thread->thread_create(this, daemonize);
}

bool Daemon::ReceiveAll()
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
      return (false);
    }
  return (true);
}

void Daemon::work()
{
  Request trash(NULL, 0);
  Response trash2(NULL, 0);
  sockaddr_in sock;
  t_socket sockint = _socket->getFD();

  call(CONNECTION_INIT, trash, trash2, sockint, sock);
  std::cout << "CONNECTION_INIT" << std::endl;
  while (isRunning())
    {
      if (!this->ReceiveAll())
	break;
      Request *tmp;
      while (!_reqs.empty())
	{
	  tmp = _reqs.front();
	  tmp->separate();
	  Response resp(NULL, 0);
	  std::cout << "BEFORE :: " << tmp->getHeader().getCommand() << " :: " <<  tmp->getHeader().getArg() << " :: on socket -> " << sockint << std::endl;
	  call(PREPROCESS_REQUEST, *(tmp), resp, sockint, sock);
	  call(PROCESS_REQUEST, *(tmp), resp, sockint, sock);
	  call(CREATE_RESPONSE, *(tmp), resp, sockint, sock);
	  call(PROCESS_FINISHED_RESPONSE, *(tmp), resp, sockint, sock);
	  call(PRESENDING_PROCESSING, *(tmp), resp, sockint, sock);
	  if (resp.getLength())
	    _socket->Send(resp.getBuffer(), resp.getLength());
	  _reqs.pop();
	  delete(tmp);
	  while (!_reqs.empty())
	    {
	      tmp = _reqs.front();
	      _reqs.pop();
	      delete(tmp);
	    }
	  break;
	}
    }
  std::cout << "CONNECTION_CLOSED" << std::endl;
  call(CONNECTION_CLOSED, trash, trash2, sockint, sock);
  _modules->detach();
  if (!_modules->isAttached())
    delete(_modules);
  _socket->Close();
  delete(_socket);
  setRunning(false);
}

void Daemon::setRunning(bool r)
{
  _mutex->MutexLock();
  _running = r;
  _mutex->MutexUnlock();
}

bool Daemon::isRunning() const
{
  _mutex->MutexLock();
  bool tmp = _running;
  _mutex->MutexUnlock();
  return (tmp);
}

void Daemon::stop()
{
  setRunning(false);
  this->_thread->thread_cancel();
}

void Daemon::call(DirectivesOrder directiveorder, Request &req, Response &resp, t_socket socket, sockaddr_in connexionInfos)
{
  std::list<ModuleContainer *>::const_iterator iter;

  for (iter = _modules->getList().begin(); iter != _modules->getList().end(); ++iter)
    {
      if ((*iter)->isLoaded() && (*iter)->_infos->managedDirectives & directiveorder)
	{
	  if ((*iter)->_infos->name == "php")
	    {
	      if (std::string::npos != req.getHeader().getArg().find(".php"))
		{
		  std::cout << "calling PHP" << std::endl;
		  (*iter)->_directives->callDirective(directiveorder, req, resp, socket, connexionInfos);
		  break;
		}
	    }
	  else
	    (*iter)->_directives->callDirective(directiveorder, req, resp, socket, connexionInfos);
	}
    }
}

Daemon::~Daemon()
{
  delete(_thread);
  delete(_mutex);
  Request *tmp;

  while (!_reqs.empty())
    {
      tmp = _reqs.front();
      _reqs.pop();
      delete(tmp);
    }

}
