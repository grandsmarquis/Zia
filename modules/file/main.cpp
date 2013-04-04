#include <iostream>
#include <string>

#include "../../trunk/apiheaders/Response.h"
#include "../../trunk/apiheaders/ModuleInfos.h"
#include "../../trunk/apiheaders/Directives.h"
#include "../../trunk/apiheaders/DirectivesOrder.h"

#include "File.hpp"

extern "C" {
  ModuleInfos * get_module_infos();
  Directives * get_directives();
}

int main()
{
  ModuleInfos * moduleInfos = get_module_infos();
  Directives * moduleDirectives = get_directives();

  std::cout << moduleInfos->associatedDLL << std::endl;
  std::cout << moduleInfos->name << std::endl;


  moduleDirectives->init();
  // moduleDirectives->callDirective(CREATE_RESPONSE, request, response);

  delete moduleDirectives;
  delete moduleInfos;

  return 0;
}
