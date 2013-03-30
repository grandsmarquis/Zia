#ifndef		__AMUTEXCROSS__
#define		__AMUTEXCROSS__

#include	"IMutex.hpp"

#ifdef		__linux__
#include	"MutexUnix.hpp"
#else
#include	"MutexCSWindows.hpp"
#endif

class	MutexCross
{
public:
  MutexCross();
  ~MutexCross();
  
public:
  bool	mutexInit();
  bool	mutexDestroy();
  bool	mutexLock();
  bool	mutexTryLock();
  bool	mutexUnlock();

private:
  IMutex* const	_mutex;
};

#endif
