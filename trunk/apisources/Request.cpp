
#include "Request.h"
#include "../HTTPParser.hpp"

Request::Request(char *buffer, int bufferLength)
  : _body(buffer, bufferLength)
{
  //  HTTPParser parser(buffer, bufferLength);
  //_header(parser.getMap(), parser.getArg(), parser.getCmd(), parser.getVersion());
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
