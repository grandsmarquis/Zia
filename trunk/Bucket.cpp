#include "Bucket.hpp"
#include <iostream>
#include <vector>

Bucket::Bucket(void)
{
}

bool Bucket::pushData(char *data, int size)
{
  data[size] = '\0';
  _str += data;
  return (false);
}

char *Bucket::getData()
{
  unsigned int l = _str.find("\r\n");
  char *ret = new char[l+1];
  std::copy(_str.begin(), _str.begin() + l, ret);
  ret[l] = '\0';
  _size = l;
  _str.erase(_str.begin(), _str.begin() + l);
  return (ret);
}

bool Bucket::canCut() const
{
  if (std::string::npos != _str.find("\r\n"))
    {
      return (true);
    }
  return (false);
}

int Bucket::getSize() const
{
  return (_size);
}

bool Bucket::isEmpty(void) const
{
  return (this->_str.empty());
}
