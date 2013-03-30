#include	"MutexCSWindows.hpp"

MutexCSWindows::MutexCSWindows()
{

}

MutexCSWindows::~MutexCSWindows()
{

}

bool	MutexCSWindows::MutexInit()
{
	InitializeCriticalSection(&this->_section);
	return (true);
}

bool	MutexCSWindows::MutexDestroy()
{
	DeleteCriticalSection(&this->_section);
    return (true);
}

bool	MutexCSWindows::MutexLock()
{
	EnterCriticalSection(&this->_section);
	return (true);
}

bool	MutexCSWindows::MutexTryLock()
{
  if (TryEnterCriticalSection(&this->_section) != 0) // This is not a mistake
    return (true);
  return (false);
}

bool	MutexCSWindows::MutexUnlock()
{
	LeaveCriticalSection(&this->_section);
    return (true);
}

void	*MutexCSWindows::getMutexPointer()
{
  return (&(this->_section));
}
