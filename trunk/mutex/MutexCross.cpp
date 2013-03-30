#include	"MutexCross.hpp"

#ifdef	__linux__
#include	"MutexUnix.hpp"

#else
#include	"MutexCSWindows.hpp"

#endif

MutexCross::MutexCross()
  :
#ifdef	__linux__
  _mutex(new MutexUnix())
#else
  _mutex(new MutexCSWindows())
#endif
{
}

MutexCross::~MutexCross()
{

}

bool	MutexCross::mutexInit()
{
  return (this->_mutex->MutexInit());
}

bool	MutexCross::mutexDestroy()
{
  return (this->_mutex->MutexDestroy());
}

bool	MutexCross::mutexLock()
{
  return (this->_mutex->MutexLock());
}

bool	MutexCross::mutexTryLock()
{
  return (this->_mutex->MutexTryLock());
}

bool	MutexCross::mutexUnlock()
{
  return (this->_mutex->MutexUnlock());
}
