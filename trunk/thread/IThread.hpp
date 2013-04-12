#ifndef		__ITHREAD__
#define		__ITHREAD__

#ifdef	_WIN32
#define _WINSOCKAPI_
#include	<windows.h>
#endif

class		IThread
{
public:
  virtual ~IThread() {}
public:
#ifdef	__unix__
  virtual void		thread_create(void *param, void *func(void *param)) = 0;
#else
  virtual void		thread_create(void *param, DWORD WINAPI func(void *param)) = 0;
#endif
  virtual void		thread_cancel() = 0;
  virtual void		thread_join() = 0;
};

#endif
