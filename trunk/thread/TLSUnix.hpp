//
// TLSUnix.hpp for R-type in /home/petit_v/svn/R-Type/trunk/common
// 
// Made by Vianney Petit
// Login   <petit_v@epitech.net>
// 
// Started on  Mon Dec 31 11:02:22 2012 Vianney Petit
// Last update Tue Jan  1 10:48:25 2013 Vianney Petit
//

#ifndef	__TLS_UNIX__
#define	__TLS_UNIX__

#include	<pthread.h>

class	TLSUnix
{
private:
  pthread_key_t	_key;
public:
  void	create();
  void	set(void* value);
  void*	get();
  void	destroy();
};

#endif
