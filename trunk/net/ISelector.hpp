//
// ISelector.hpp for babel in /home/petit_v/svn/babel-2015-demouc_m/trunk/common/src
// 
// Made by Vianney Petit
// Login   <petit_v@epitech.net>
// 
// Started on  Sun Nov 25 11:45:28 2012 Vianney Petit
// Last update Tue Dec  4 15:55:45 2012 Vianney Petit
//

#ifndef	__ISELECTOR_HH__
#define	__ISELECTOR_HH__

#include	"../net/ISocket.hh"

class	ISelector
{
public:
  enum e_type{T_ERR, T_READ, T_WRITE, T_READWRITE, T_HANG};
public:
  virtual void		clear() = 0;
  virtual int		addSocket(net::ISocket*, e_type) = 0;
  virtual void		changeSocket(int id, e_type type) = 0;
  virtual net::ISocket*	removeSocket(int id) = 0;
  virtual void		select(int timeout = 500) = 0;
  virtual net::ISocket*	getNextSock(e_type&) = 0;
};

#endif
