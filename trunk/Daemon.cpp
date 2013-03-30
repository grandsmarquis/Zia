
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



Daemon::Daemon(net::ISocket *socket, int port)
  : _socket(socket), _port(port), _running(true)
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
	  std::cout << _b.getData() << std::endl;
	}
    }
}

void Daemon::work()
{
  bool status = false;
  
  std::cout << "CONNECTION_INIT" << std::endl;
  while (this->_running)
    {
      this->ReceiveAll();
      /*
	std::cout << "PREPROCESS_REQUEST" << std::endl;
	std::cout << "PROCESS_REQUEST" << std::endl;
	std::cout << "CREATE_RESPONSE" << std::endl;
	std::cout << "PROCESS_FINISHED_RESPONSE" << std::endl;
	std::cout << "PRESENDING_PROCESSING" << std::endl;
      */
      if (status)
	{
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
