#ifndef FILE_HPP__
#define FILE_HPP__ 1

#include "../../trunk/apiheaders/Directives.h"

class File : public Directives
{
  public:
    File();
    virtual ~File();
    virtual void callDirective(DirectivesOrder, Request &);
    virtual void callDirective(DirectivesOrder, Response &);
    virtual void init();

  private:
    void cryptResponse(Response &);
    void uncryptRequest(Request &);
    void sendIdx(Response &);
    int _idx;
};


#endif
