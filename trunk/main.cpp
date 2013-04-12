
#include <iostream>
#ifdef __unix__
#include <unistd.h>
#elif defined _WIN32
#define _WINSOCKAPI_
#include <windows.h>
#endif
#include <string>

#include "apiheaders/Response.h"
#include "apiheaders/ModuleInfos.h"
#include "apiheaders/Directives.h"
#include "apiheaders/DirectivesOrder.h"

#include "EmbededObjectFactory.hpp"
#include "DaemonManager.hpp"
#include "ConfigManager.hpp"

int main()
{
  DaemonManager manager;
  ConfigManager config("../default.cfg");
  
  
  manager.loadConf(config);
  while (true)
    {
#ifdef __unix__
      usleep(1000);
#elif defined _WIN32
      Sleep(30);
#endif
      manager.update();
    }

  return 0;
}
