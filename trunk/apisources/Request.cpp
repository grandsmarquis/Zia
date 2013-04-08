
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
  int buffer_length;

  buffer_length = this->_body.getBodyLength();
  if (buffer_length > 0)
  {
    char * body;

    body = this->_body.getBody();

    HTTPParser parser(body, buffer_length);

    _header.setCommand(parser.getCmd());
    _header.setArg(parser.getArg());
    _header.setVersion(parser.getVersion());
    for (std::map<std::string, std::string>::const_iterator it = parser.getMap().begin(); it != parser.getMap().end(); ++it)
    {
      _header.setValue(it->first, it->second);
    }
  }
}
