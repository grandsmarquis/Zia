
#include <iostream>
#include <string>

#include "../../trunk/apiheaders/ModuleInfos.h"
#include "../../trunk/apiheaders/Directives.h"
#include "../../trunk/apiheaders/DirectivesOrder.h"

#include "File.hpp"

extern "C"
{
  ModuleInfos * get_module_infos()
  {
    ModuleInfos *m = new ModuleInfos;

    m->associatedDLL = "File";
    m->managedDirectives = CREATE_RESPONSE; // CONNECTION_INIT | PREPROCESS_REQUEST | PROCESS_FINISHED_RESPONSE;
    m->managesHeaderOnly = true;
    m->name = "file";
    m->nbDirectives = 1;
    return (m);
  }

  Directives * get_directives()
  {
    return (new File());
  }
}

File::File()
{
}

File::~File()
{
  std::cout << "destruct file" << std::endl;
}

void File::init()
{
  std::cout << "init file" << std::endl;
}

void File::callDirective(DirectivesOrder dir, Request & req)
{
  /*
  if (dir == PREPROCESS_REQUEST)
    this->uncryptRequest(req);
  */
}

void File::callDirective(DirectivesOrder dir, Response & res)
{
  if (dir == CREATE_RESPONSE) {
    std::cout << "hello world" << std::endl;
  }
  /*
  if (dir == CONNECTION_INIT)
    this->sendIdx(res);
  else if (dir == PROCESS_FINISHED_RESPONSE)
    this->cryptResponse(res);
  */
}
