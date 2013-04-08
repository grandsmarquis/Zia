
#ifndef __BUCKET_HH__
#define __BUCKET_HH__

#include <stdio.h>
#include <cstring>
#include <string>

class Bucket
{

public:
  Bucket(void);
  bool pushData(char *data, int size);
  int getSize(void) const;
  bool isEmpty(void) const;
  char *getData(void);
  bool canCut() const;
private:
  std::string _str;
  bool _b;
  int _size;
};

#endif
