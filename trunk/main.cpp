
#include <iostream>
#ifdef __unix__
#include <unistd.h>
#elif defined _WIN32
#define _WINSOCKAPI_
#include <windows.h>
#endif
#include <string>

#ifdef _WIN32
#include "export.h"
#endif

#include "apiheaders/Response.h"
#include "apiheaders/ModuleInfos.h"
#include "apiheaders/Directives.h"
#include "apiheaders/DirectivesOrder.h"

#include "EmbededObjectFactory.hpp"
#include "DaemonManager.hpp"
#include "ConfigManager.hpp"

#ifdef __unix__
int main()
#elif defined _WIN32
void zia_main()
#endif
{
  DaemonManager manager;
#ifdef __unix__
  ConfigManager config("../Linux.cfg");
#elif defined _WIN32
  ConfigManager config("../Windows.cfg");
#endif

  
#ifdef	_WIN32
  WSADATA wsaData;
  if(WSAStartup(0x202, &wsaData))
    throw;
#endif
  
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
 
#ifdef	_WIN32
  WSACleanup();
#endif

#ifdef __unix__
  return 0;
#endif
}
