
#include "Request.h"
#include "../HTTPParser.hpp"

Request::Request(char *buffer, int bufferLength)
  : _buffer(NULL), _bufferLength(0), _body(buffer, bufferLength)
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

RequestHeader & Request::getHeader()
{
  return (_header);
}

int Request::getLength() const
{
  return (_bufferLength);
}

void Request::separate()
{
  char * body;
  int buffer_length;

  body = this->_body.getBody();
  buffer_length = this->_body.getBodyLength();

  HTTPParser parser(body, buffer_length);

  _header.setCommand(parser.getCmd());
  _header.setArg(parser.getArg());
  _header.setVersion(parser.getVersion());
  for (std::map<std::string, std::string>::const_iterator it = parser.getMap().begin(); it != parser.getMap().end(); ++it)
  {
    _header.setValue(it->first, it->second);
  }
}
