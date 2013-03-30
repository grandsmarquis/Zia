#ifndef		__THREADUNIX__
#define		__THREADUNIX__

#include	<pthread.h>
#include	"IThread.hpp"

class		ThreadUnix : public IThread
{
 public:
  ThreadUnix();
  ~ThreadUnix();


public:
  void		thread_create(void *param, void *func(void *param));
  void		thread_cancel();
  void		thread_join();

private:
  pthread_t						_ownThread;
};

#endif
