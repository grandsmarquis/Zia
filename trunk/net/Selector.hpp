//
// Selector.hpp for babel in /home/petit_v/svn/babel-2015-demouc_m/trunk/common/src
// 
// Made by Vianney Petit
// Login   <petit_v@epitech.net>
// 
// Started on  Thu Nov 22 20:14:29 2012 Vianney Petit
// Last update Tue Dec  4 15:55:28 2012 Vianney Petit
//

#ifndef	__SELECTOR_HH__
#define	__SELECTOR_HH__

#ifdef __unix__
#include	<poll.h>
#include	"AUnixSocket.hh"
#elif defined _WIN32
#include	"AWindowsSocket.hh"
#endif
#include	"ISelector.hpp"

class	Selector : public ISelector
{
private:
#ifdef __unix__
  struct pollfd			_fdSet[1024];
#elif defined _WIN32
  WSAPOLLFD			_fdSet[1024];
#endif
  net::ISocket*			_fdShadow[1024];
  int				_idx;
  int				_it;
public:
  Selector();
  void		clear();
  int		addSocket(net::ISocket*, e_type);
  void		changeSocket(int id, e_type type);
  net::ISocket*	removeSocket(int id);
  void		select(int timeout = 500);
  net::ISocket*	getNextSock(e_type&);
};

#endif
