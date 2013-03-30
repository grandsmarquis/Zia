
#include "Response.h"

Response::Response(char *buffer, int bufferLength)
  :_body(buffer, bufferLength)
{
}

Response::~Response()
{
}

Body	&Response::getBody()
{
  return (_body);
}

char	*Response::getBuffer()
{
  return (_buffer);
}

ResponseHeader &Response::getHeader()
{
  return (_header);
}

int Response::getLength() const
{
  return (_bufferLength);
}

void Response::assemble()
{
}
