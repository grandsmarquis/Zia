#ifndef PHP_MODULE_HPP__
#define PHP_MODULE_HPP__ 1

#include <map>

#include "../../trunk/apiheaders/Directives.h"
#include "../../trunk/apiheaders/DirectivesOrder.h"

#include "../../trunk/apiheaders/Request.h"
#include "../../trunk/apiheaders/Response.h"

class PHPModule : public Directives
{
  private:
    const char ** buildEnv(RequestHeader & requestHeader) const;

  public:
    PHPModule();
    virtual ~PHPModule();
    virtual void callDirective(DirectivesOrder directiveorder, Request & request, Response & response);
    virtual void init();
};


#endif
