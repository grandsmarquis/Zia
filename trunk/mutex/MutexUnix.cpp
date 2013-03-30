#include	"MutexUnix.hpp"

MutexUnix::MutexUnix()
{

}

MutexUnix::~MutexUnix()
{

}

bool	MutexUnix::MutexInit()
{
  if (pthread_mutex_init(&this->_mutex, NULL) == 0)
    return (true);
  return (false);
}

bool	MutexUnix::MutexDestroy()
{
  if (pthread_mutex_destroy(&this->_mutex) == 0)
    return (true);
  return (false);
}

bool	MutexUnix::MutexLock()
{
  if (pthread_mutex_lock(&this->_mutex) == 0)
    return (true);
  return (false);
}

bool	MutexUnix::MutexTryLock()
{
  if (pthread_mutex_trylock(&this->_mutex) == 0)
    return (true);
  return (false);
}

bool	MutexUnix::MutexUnlock()
{
  if (pthread_mutex_unlock(&this->_mutex) == 0)
    return (true);
  return (false);
}

void	*MutexUnix::getMutexPointer()
{
  return (&(this->_mutex));
}
