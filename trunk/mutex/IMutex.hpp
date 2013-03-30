#ifndef		__IMUTEX_HH__
#define		__IMUTEX_HH__

class		IMutex
{
public:
  virtual bool	MutexInit() = 0;
  virtual bool	MutexDestroy() = 0;
  virtual bool	MutexLock() = 0;
  virtual bool	MutexTryLock() = 0;
  virtual bool	MutexUnlock() = 0;
  virtual void	*getMutexPointer() = 0;
};

#endif
