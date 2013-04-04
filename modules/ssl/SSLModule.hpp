#ifndef SSL_MODULE_HPP__
#define SSL_MODULE_HPP__ 1

#include <map>
#include <string>

#include "../../trunk/apiheaders/Directives.h"
#include "../../trunk/apiheaders/DirectivesOrder.h"

#include "../../trunk/apiheaders/Request.h"
#include "../../trunk/apiheaders/Response.h"

class SSLModule : public Directives
{
  private:

  public:
    SSLModule();
    virtual ~SSLModule();
    virtual void callDirective(DirectivesOrder directiveorder, Request & request, Response & response);
    virtual void init();
    std::string get_password() const;
    
};


#endif
