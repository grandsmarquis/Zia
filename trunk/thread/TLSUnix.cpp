//
// TLSUnix.cpp for R-type in /home/petit_v/svn/R-Type/trunk/common
// 
// Made by Vianney Petit
// Login   <petit_v@epitech.net>
// 
// Started on  Mon Dec 31 11:05:50 2012 Vianney Petit
// Last update Mon Dec 31 19:11:59 2012 Vianney Petit
//

#include	"TLSUnix.hpp"

void	TLSUnix::create()
{
  int		ret;

  ret = pthread_key_create(&_key, NULL);
  if (ret != 0)
    throw;
}

void	TLSUnix::set(void* value)
{
  pthread_setspecific(_key, value);
}

void*	TLSUnix::get()
{
  return (pthread_getspecific(_key));
}

void	TLSUnix::destroy()
{
  pthread_key_delete(_key);
}
