
#include "Body.h"

Body::Body(char *body, int lenght)
  :_body(body), _length(lenght)
{
}

Body::~Body()
{
  if (_length)
    delete[] (_body);
}

char *Body::getBody()
{
  return (_body);
}

int Body::getBodyLength() const
{
  return (_length);
}

void Body::setBody(char *body, int lenght)
{
  this->_body = body;
  this->_length = lenght;
}
