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
  std::string str3 = _str.substr(_str.find("\r\n"));
  char * writable = new char[str3.size() + 1];
  std::copy(_str.begin(), str3.end(), writable);
  writable[str3.size()] = '\0';
  _str.erase(0, str3.size());
  _size = str3.size();
  return (writable);
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
