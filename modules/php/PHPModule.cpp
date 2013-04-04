
#include <unistd.h>

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

#include "../../trunk/apiheaders/ModuleInfos.h"
#include "../../trunk/apiheaders/Directives.h"
#include "../../trunk/apiheaders/DirectivesOrder.h"

#include "PHPModule.hpp"

extern "C"
{
  ModuleInfos * get_module_infos()
  {
    ModuleInfos *m = new ModuleInfos;

    m->associatedDLL = "php";
    m->managedDirectives = CREATE_RESPONSE; // CONNECTION_INIT | PREPROCESS_REQUEST | PROCESS_FINISHED_RESPONSE;
    m->managesHeaderOnly = true;
    m->name = "php";
    m->nbDirectives = 1;
    return (m);
  }

  Directives * get_directives()
  {
    return (new PHPModule());
  }
}

PHPModule::PHPModule()
{
}

PHPModule::~PHPModule()
{
}

void PHPModule::init()
{
  char *env[] = {
    "DOCUMENT_ROOT=/mnt/hgfs/william/GitHub/jdourlens/Zia/modules/php",
    "GATEWAY_INTERFACE=CGI/1.1",
    "HOME=/home/SYSTEM",
    "HTTP_ACCEPT=text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
    "HTTP_ACCEPT_CHARSET=ISO-8859-1,utf-8;q=0.7,*;q=0.7",
    "HTTP_ACCEPT_ENCODING=gzip, deflate",
    "HTTP_ACCEPT_LANGUAGE=en-us,en;q=0.5",
    "HTTP_CONNECTION=keep-alive",
    "HTTP_HOST=example.com",
    "HTTP_USER_AGENT=Mozilla/5.0 (Windows NT 6.1; WOW64; rv:5.0) Gecko/20100101 Firefox/5.0",
    "PATH=/home/SYSTEM/bin:/bin:/cygdrive/c/progra~2/php:/cygdrive/c/windows/system32:...",
    "PATHEXT=.COM;.EXE;.BAT;.CMD;.VBS;.VBE;.JS;.JSE;.WSF;.WSH;.MSC",
    "PATH_INFO=/mnt/hgfs/william/GitHub/jdourlens/Zia/modules/php",
    "PATH_TRANSLATED=/mnt/hgfs/william/GitHub/jdourlens/Zia/modules/php",
    "QUERY_STRING=var1=value1&var2=with%20percent%20encoding",
    "REMOTE_ADDR=127.0.0.1",
    "REMOTE_PORT=63555",
    "REQUEST_METHOD=GET",
    "REQUEST_URI=/index.php/foo/bar?var1=value1&var2=with%20percent%20encoding",
    "SCRIPT_FILENAME=/mnt/hgfs/william/GitHub/jdourlens/Zia/modules/php/index.php",
    "SCRIPT_NAME=/index.php",
    "SERVER_ADDR=127.0.0.1",
    "SERVER_ADMIN=(server admin's email address)",
    "SERVER_NAME=127.0.0.1",
    "SERVER_PORT=80",
    "SERVER_PROTOCOL=HTTP/1.1",
    "SERVER_SIGNATURE=",
    "SERVER_SOFTWARE=Apache/2.2.19 (Win32) PHP/5.2.17",
    "SYSTEMROOT=/",
    "REDIRECT_STATUS=true"
  };

  execvpe("/usr/bin/php5-cgi", NULL, env);
}

void PHPModule::callDirective(DirectivesOrder directiveorder, Request & request, Response & response)
{
}
