#ifndef		__MUTEX_CSWINDOWS__
#define		__MUTEX_CSWINDOWS__
#define _WINSOCKAPI_
#include	<Windows.h>
#include	"IMutex.hpp"

class	MutexCSWindows :public IMutex
{
public:
  MutexCSWindows();
  virtual ~MutexCSWindows();
  virtual bool	MutexInit();
  virtual bool	MutexDestroy();
  virtual bool	MutexLock();
  virtual bool	MutexTryLock();
  virtual bool	MutexUnlock();
  virtual void	*getMutexPointer();
  
private:
  CRITICAL_SECTION _section;
};

#endif
