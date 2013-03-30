#ifndef FILE_HPP__
#define FILE_HPP__ 1

#include "../../trunk/apiheaders/Directives.h"
#include "../../trunk/apiheaders/DirectivesOrder.h"

#include "../../trunk/apiheaders/Request.h"
#include "../../trunk/apiheaders/Response.h"

class File : public Directives
{
  public:
    File();
    virtual ~File();
    virtual void callDirective(DirectivesOrder, Request &);
    virtual void callDirective(DirectivesOrder, Response &);
    virtual void init();
};


#endif
