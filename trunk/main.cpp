
#include <iostream>

#include <string>

#include "apiheaders/Response.h"
#include "apiheaders/ModuleInfos.h"
#include "apiheaders/Directives.h"
#include "apiheaders/DirectivesOrder.h"

#include "EmbededObjectFactory.hpp"
#include "DaemonManager.hpp"

int main()
{
  EmbededObjectFactory objectFactory("../modules/");
  Response response(NULL, 0);
  Request request(NULL, 0);

  ModuleInfos * moduleInfos = objectFactory.getModuleInfos("file/file");
  Directives * moduleDirectives = objectFactory.getModuleDirectives("file/file");

  std::cout << moduleInfos->associatedDLL << std::endl;
  std::cout << moduleInfos->name << std::endl;


  moduleDirectives->init();
  moduleDirectives->callDirective(CREATE_RESPONSE, request, response);

  delete moduleDirectives;
  delete moduleInfos;



  DaemonManager manager;
  manager.addPort(3030);
  manager.addPort(2020);
  manager.addPort(80);
  while (true)
    manager.update();

  return 0;
}
