
#include "Request.h"

Request::Request(char *buffer, int bufferLength)
  : _body(buffer, bufferLength)
{
}

Request::~Request()
{
}

Body	&Request::getBody()
{
  return (_body);
}

char	*Request::getBuffer()
{
  return (_buffer);
}

RequestHeader &Request::getHeader()
{
  return (_header);
}

int Request::getLength() const
{
  return (_bufferLength);
}

void Request::separate()
{
}
