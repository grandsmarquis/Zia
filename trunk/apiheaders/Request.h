#ifndef __REQUEST_H__
# define	__REQUEST_H__

#include "RequestHeader.h"
#include "Body.h"

class Request {
  private:
    char *_buffer;
    int _bufferLength;
    Body _body;
    RequestHeader _header;

  public:
    Request (char *buffer, int bufferLength);
    ~Request ();
    Body & getBody();
    char *getBuffer();
    RequestHeader & getHeader();
    int getLength() const;
    void separate();
};

#endif // !_REQUEST_H_
