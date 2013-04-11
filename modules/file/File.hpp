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
    std::string _getContentType(std::string const & path);

  public:
    File();
    virtual ~File();
    virtual void callDirective(DirectivesOrder directiveorder, Request & request, Response & response, t_socket socket, struct sockaddr_in & connexionInfos);
    virtual void init();
};


#endif
