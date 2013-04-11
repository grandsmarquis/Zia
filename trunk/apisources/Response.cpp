
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <string>

#include "Response.h"

#define EOL "\r\n"

Response::Response(char *buffer, int bufferLength)
  :_buffer(NULL), _bufferLength(0), _body(buffer, bufferLength)
{
}

Response::~Response()
{
  if (_bufferLength > 0)
    delete[] (_buffer);
}

Body	&Response::getBody()
{
  return (_body);
}

char	*Response::getBuffer()
{
  return (_buffer);
}

ResponseHeader & Response::getHeader()
{
  return (this->_header);
}

int Response::getLength() const
{
  return (_bufferLength);
}

void Response::assemble()
{
  std::string out;
  char s = ' ';

  out
    .append(_header.getVersion())
    .append(1, s)
    .append(_header.getStatusCode())
    .append(1, s)
    .append(_header.getStatusMessage())
    .append(EOL);

  std::map<std::string, std::string> const & options = _header.getOptions();
  std::map<std::string, std::string>::const_iterator it;

  for (it = options.begin(); it != options.end(); ++it) {
    out.append(it->first).append(": ").append(it->second).append(EOL);
  }
  char str[10];
  snprintf(str, 10, "%d", _body.getBodyLength());
  out.append("Content-Length").append(": ").append(str).append(EOL);
  out.append(EOL).append(_body.getBody(), _body.getBodyLength());

  size_t size = out.size();
  
  if (_buffer)
    delete(_buffer);
  _buffer = new char[size];
  out.copy(_buffer, size);
  _bufferLength = size;
}
