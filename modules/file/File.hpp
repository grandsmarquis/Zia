#ifndef FILE_HPP__
#define FILE_HPP__ 1

#include <map>

#include "../../trunk/apiheaders/Directives.h"
#include "../../trunk/apiheaders/DirectivesOrder.h"

#include "../../trunk/apiheaders/Request.h"
#include "../../trunk/apiheaders/Response.h"

class File : public Directives
{
  private:

    static int toto;
    /*
    static struct {
      char *ext;
      char *contentType;
    } _contentTypes[] = {
      {"html", "text/html"},
      {"htm", "text/html"}
    };
    */

    void _getEncoding(char *buff);

  public:
    File();
    virtual ~File();
    virtual void callDirective(DirectivesOrder directiveorder, Request & request, Response & response);
    virtual void init();
};


#endif
