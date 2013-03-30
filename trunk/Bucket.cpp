#include "Bucket.hpp"

Bucket::Bucket(void)
{
}

void Bucket::pushData(char *data)
{
  char *pnt;
  pnt = strtok(data, "\n");
  while (pnt != NULL)
    {
      _q.push(new std::string(pnt));
      pnt = strtok(NULL, "\n");
    }
}

std::string *Bucket::popLine(void)
{
  std::string *tmp = this->_q.front();
  this->_q.pop();
  return (tmp);
}

std::string *Bucket::peekLine(void)
{
  return (this->_q.front());
}

bool Bucket::isEmpty(void) const
{
  return (this->_q.size() == 0);
}
