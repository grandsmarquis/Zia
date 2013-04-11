#include <iostream>
#include <string>

#include "../../trunk/apiheaders/Response.h"
#include "../../trunk/apiheaders/ModuleInfos.h"
#include "../../trunk/apiheaders/Directives.h"
#include "../../trunk/apiheaders/DirectivesOrder.h"

#include "PHPModule.hpp"

extern "C" {
  ModuleInfos * get_module_infos();
  Directives * get_directives();
}

int main()
{
  ModuleInfos * moduleInfos = get_module_infos();
  Directives * moduleDirectives = get_directives();

  // std::cout << moduleInfos->associatedDLL << std::endl;
  // std::cout << moduleInfos->name << std::endl;
  std::string req(
      "GET /index.php?toto=tutu&tata=titi HTTP/1.0\n"
      "Host: example.com\n"
      "Referer: http://example.com/\n"
      "User-Agent: CERN-LineMode/2.15 libwww/2.17b3\n"
  );

  int size = req.size();
  char *buff = new char[size];

  req.copy(buff, size);

  Request request(buff, size);
  Response response(NULL, 0);

  request.separate();

  moduleDirectives->init();
  moduleDirectives->callDirective(CREATE_RESPONSE, request, response);

  response.assemble();

  std::string out;
  out.append(response.getBuffer(), response.getLength());
  std::cout << out << std::endl;

  delete moduleDirectives;
  delete moduleInfos;

  return 0;
}
