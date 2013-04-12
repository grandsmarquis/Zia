#ifndef	__TLS_WINDOWS
#define	__TLS_WINDOWS

#define _WINSOCKAPI_
#include <windows.h>

class	TLSWindows
{
private:
  DWORD	_key;
public:
  void	create();
  void	set(LPVOID value);
  LPVOID	get();
  void	destroy();
};

#endif
