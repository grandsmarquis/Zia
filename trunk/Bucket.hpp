
#ifndef __BUCKET_HH__
#define __BUCKET_HH__

#include <string>
#include <iostream>
#include <sstream>

#include <stdio.h>
#include <cstring>

#include <queue>

class Bucket
{

public:
  Bucket(void);
  void pushData(char *data);
  std::string *popLine(void);
  std::string *peekLine(void);
  bool isEmpty() const;

private:
  std::string _tmp;
  std::queue<std::string *> _q;
  bool _b;
};

#endif
