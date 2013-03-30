#include	"ThreadWindows.hpp"

ThreadWindows::ThreadWindows()
{

}

ThreadWindows::~ThreadWindows()
{

}

void	ThreadWindows::thread_create(void *param, DWORD WINAPI func(void *param))
{
  this->_ownThread = CreateThread(NULL, 0, func, param, 0, 0);
}

void	ThreadWindows::thread_cancel()
{
  TerminateThread(this->_ownThread, 0);
}

void	ThreadWindows::thread_join()
{
  WaitForSingleObject(this->_ownThread, INFINITE);
}
