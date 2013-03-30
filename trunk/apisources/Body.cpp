
#include "Body.h"

Body::Body(char *body, int lenght)
{
}

Body::~Body()
{
}

char *getBody()
{
  return (_body);
}

int getBodyLength() const
{
  return (_length);
}

void setBody(char *body, int lenght)
{
  this->_body = body;
  this->_length = lenght;
}
