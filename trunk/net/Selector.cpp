//
// Selector.cpp for babel in /home/petit_v/svn/babel-2015-demouc_m/trunk/common/src
// 
// Made by Vianney Petit
// Login   <petit_v@epitech.net>
// 
// Started on  Thu Nov 22 21:14:59 2012 Vianney Petit
// Last update Tue Dec  4 15:55:11 2012 Vianney Petit
//

#include	"Selector.hpp"
#include	<cstdio>

Selector::Selector()
  : _idx(0), _it(0)
{
}

void	Selector::clear()
{
  _idx = 0;
  _it = 0;
}

int	Selector::addSocket(net::ISocket* tmpSock, e_type type)
{
#ifdef __unix__
  net::AUnixSocket*	sock;
#elif defined _WIN32
	net::AWindowsSocket* sock;
#endif
  if (_idx >= 1024)
    {
      printf("Selector: FD LIMIT REACHED. Not acepting any more\n");
      return (-1);
    }
  printf("Selector: ADDED NEW FD. idx: %d\n", _idx);
#ifdef __unix__
  if ((sock = dynamic_cast<net::AUnixSocket*>(tmpSock)) == NULL)
    throw;
#elif defined _WIN32
  if ((sock = dynamic_cast<net::AWindowsSocket*>(tmpSock)) == NULL)
    throw;
#endif
  _fdSet[_idx].fd = sock->GetSocketRepresentation();
  if (type == T_READ)
    _fdSet[_idx].events = POLLIN;
  else if (type == T_WRITE)
    _fdSet[_idx].events = POLLOUT;
  else if (type == T_READWRITE)
    _fdSet[_idx].events = POLLIN | POLLOUT;
  _fdSet[_idx].revents = 0;
  _fdShadow[_idx] = sock;
  _idx++;
  return (_idx - 1);
}

void	Selector::changeSocket(int id, e_type type)
{
  if (type == T_READ)
    _fdSet[id].events = POLLIN;
  else if (type == T_WRITE)
    _fdSet[id].events = POLLOUT;
  else if (type == T_READWRITE)
    _fdSet[id].events = POLLIN | POLLOUT;
}

net::ISocket*	Selector::removeSocket(int id)
{
  if (id != _idx - 1)
    {
      memcpy(&_fdSet[id], &_fdSet[_idx - 1], sizeof(struct pollfd));
      _fdShadow[id] = _fdShadow[_idx - 1];
    }
  _idx--;
  _it--;
  printf("Selector: REMOVED OLD FD. idx: %d\n", _idx);
  return (_fdShadow[id]);
}

void	Selector::select(int timeout)
{
  int	dbg;
#ifdef __unix__
  if ((dbg = poll(_fdSet, _idx, timeout)) != 0)
#elif defined _WIN32
  if ((dbg = WSAPoll(_fdSet, _idx, timeout)) != 0)
#endif
    _it = 0;
  else
    {
      _it = _idx;
    }
}

net::ISocket*	Selector::getNextSock(e_type& type)
{
  while (_it < _idx)
    {
      type = T_ERR;
      if ((_fdSet[_it].revents & POLLHUP) || (_fdSet[_it].revents & POLLERR))
	{
	  printf("/!\\ getNextSock: %d\n", _fdSet[_it].revents);
	  type = T_HANG;
	}
      else
	{
	  if (_fdSet[_it].revents & POLLIN)
	    type = T_READ;
	  if (_fdSet[_it].revents & POLLOUT) {
	    if (type == T_READ)
	      type = T_READWRITE;
	    else
	      type = T_WRITE;
	  }
	}
      _it++;
      if (type != T_ERR)
	{
	  return (_fdShadow[_it - 1]);
	}
    }
  return (NULL);
}
