
#ifndef __BUCKET_HH__
#define __BUCKET_HH__

#include <stdio.h>
#include <cstring>

class Bucket
{

public:
  Bucket(void);
  void pushData(char *data, int size);
  int getSize(void) const;
  bool isEmpty(void) const;
  char *getData(void);
private:
  int _size;
  char *_data;
  bool _b;
};

#endif
