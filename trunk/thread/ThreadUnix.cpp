#include	"ThreadUnix.hpp"

ThreadUnix::ThreadUnix()
{
}

ThreadUnix::~ThreadUnix()
{
}

void	ThreadUnix::thread_create(void *param, void *func(void *param))
{
  pthread_create(&(this->_ownThread), NULL, func, param);
}

void	ThreadUnix::thread_cancel()
{
  pthread_cancel(this->_ownThread);
}

void	ThreadUnix::thread_join()
{
  pthread_join(this->_ownThread, 0);
}
