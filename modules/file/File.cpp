
#include <string>

#include "../../trunk/apiheaders/ModuleInfos.h"

#include "File.hpp"

extern "C"
{
  ModuleInfos * get_module_infos()
  {
    ModuleInfos *m = new ModuleInfos;

    m->associatedDLL = "File";
    m->managedDirectives = CONNECTION_INIT | PREPROCESS_REQUEST | PROCESS_FINISHED_RESPONSE;
    m->managesHeaderOnly = true;
    m->name = "file";
    m->nbDirectives = 3;
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
}

void File::init()
{

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
  /*
  if (dir == CONNECTION_INIT)
    this->sendIdx(res);
  else if (dir == PROCESS_FINISHED_RESPONSE)
    this->cryptResponse(res);
    */
}
