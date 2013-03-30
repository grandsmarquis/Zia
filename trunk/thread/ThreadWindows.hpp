#ifndef		__THREADWINDOWS__
#define		__THREADWINDOWS__

#include	"IThread.hpp"

class		ThreadWindows : public IThread
{
 public:
  ThreadWindows();
  ~ThreadWindows();

public:
  void		thread_create(void *param, DWORD WINAPI func(void *param));
  void		thread_cancel();
  void		thread_join();

private:
  HANDLE	_ownThread;
};

#endif
