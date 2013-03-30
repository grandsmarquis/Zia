#include "Bucket.hpp"

Bucket::Bucket(void)
  :_size(0), _b(true)
{
}

void Bucket::pushData(char *data, int size)
{
  char *tmp;

  if (size > 0)
    {
      if (_b)
	{
	  _b = false;
	  _data = new (char[size]);
	  memcpy(_data, data, size);
	}
      else
	{
	  tmp = new char[size + _size];
	  memcpy(tmp, _data, _size);
	  memcpy(&(tmp[_size]), data, size);
	  delete(_data);
	  _data = tmp;
	}
      _size += size;
    }
}

char *Bucket::getData()
{
  return (this->_data);
}

int Bucket::getSize() const
{
  return (this->_size);
}

bool Bucket::isEmpty(void) const
{
  return (this->_b);
}
