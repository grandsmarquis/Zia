#include	"TLSWindows.hpp"

void	TLSWindows::create()
{
  this->_key = TlsAlloc();
  if (this->_key == TLS_OUT_OF_INDEXES)
    throw;
}

void	TLSWindows::set(LPVOID value)
{
  TlsSetValue(this->_key, value);
}

LPVOID	TLSWindows::get()
{
  return (TlsGetValue(this->_key));
}

void	TLSWindows::destroy()
{
  TlsFree(this->_key);
}
