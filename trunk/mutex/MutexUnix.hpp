#ifndef		__MUTEX_UNIX__
#define		__MUTEX_UNIX__

#include	<pthread.h>

#include	"IMutex.hpp"

class	MutexUnix :public IMutex
{
public:
  MutexUnix();
  virtual ~MutexUnix();
  virtual bool	MutexInit();
  virtual bool	MutexDestroy();
  virtual bool	MutexLock();
  virtual bool	MutexTryLock();
  virtual bool	MutexUnlock();
  virtual void	*getMutexPointer();
  
private:
  pthread_mutex_t _mutex;
};

#endif
