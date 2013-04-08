
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <fstream>
#include <iostream>
#include <map>
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
}

void PHPModule::callDirective(DirectivesOrder directiveorder, Request & request, Response & response)
{
  std::map<std::string, std::string> env;

  env["DOCUMENT_ROOT"] = "/mnt/hgfs/william/GitHub/jdourlens/Zia/modules/php";
  env["GATEWAY_INTERFACE"] = "CGI/1.1";
  env["HOME"] = "/home/SYSTEM";
  env["HTTP_ACCEPT"] = "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8";
  env["HTTP_ACCEPT_CHARSET"] = "ISO-8859-1,utf-8;q=0.7,*;q=0.7";
  env["HTTP_ACCEPT_ENCODING"] = "gzip, deflate";
  env["HTTP_ACCEPT_LANGUAGE"] = "en-us,en;q=0.5";
  env["HTTP_CONNECTION"] = "keep-alive";
  env["HTTP_HOST"] = "example.com";
  env["HTTP_USER_AGENT"] = "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:5.0) Gecko/20100101 Firefox/5.0";
  env["PATH"] = "/home/SYSTEM/bin:/bin:/cygdrive/c/progra~2/php:/cygdrive/c/windows/system32:...";
  env["PATHEXT"] = ".COM;.EXE;.BAT;.CMD;.VBS;.VBE;.JS;.JSE;.WSF;.WSH;.MSC";
  env["PATH_INFO"] = "/mnt/hgfs/william/GitHub/jdourlens/Zia/modules/php";
  env["PATH_TRANSLATED"] = "/mnt/hgfs/william/GitHub/jdourlens/Zia/modules/php";
  env["QUERY_STRING"] = "var1=value1&var2=with%20percent%20encoding";
  env["REMOTE_ADDR"] = "127.0.0.1";
  env["REMOTE_PORT"] = "63555";
  env["REQUEST_METHOD"] = "GET";
  env["REQUEST_URI"] = "/index.php/foo/bar?var1=value1&var2=with%20percent%20encoding";
  env["SCRIPT_FILENAME"] = "/mnt/hgfs/william/GitHub/jdourlens/Zia/modules/php/index.php";
  env["SCRIPT_NAME"] = "/index.php";
  env["SERVER_ADDR"] = "127.0.0.1";
  env["SERVER_ADMIN"] = "(server admin's email address)";
  env["SERVER_NAME"] = "127.0.0.1";
  env["SERVER_PORT"] = "80";
  env["SERVER_PROTOCOL"] = "HTTP/1.1";
  env["SERVER_SIGNATURE"] = "";
  env["SERVER_SOFTWARE"] = "a.out server";
  env["SYSTEMROOT"] = "/";
  env["REDIRECT_STATUS"] = "true";

  const char **e = new const char*[env.size() + 1];
  int i = 0;

  std::map<std::string, std::string>::iterator it;
  for (it = env.begin(); it != env.end(); ++it) {
    std::string s(it->first + "=" + it->second);
    int size = s.size();
    char *buff  = new char[size + 1];
    s.copy(buff, size);
    s[size] = 0;
    e[i] = buff;
    ++i;
  }
  e[i] = NULL;
  char *argv[] = {
    NULL
  };

  pid_t pid;

  int pipe_fds[2];

  pipe(pipe_fds);

  pid = fork();
  if (pid == -1) {
    std::cerr << "unable to fork" << std::endl;
  } else {
    if (pid == 0) {

      close(pipe_fds[0]);
      dup2(pipe_fds[1], 1);
      std::cout << execve("/usr/bin/php-cgi", argv, const_cast<char * const*> (e)) << std::endl;
      exit(1);
    } else {
      close(pipe_fds[1]);

      waitpid(pid, NULL, 0);

      char buff[128];
      std::string bdy;
      int size;
      size = read(pipe_fds[0], buff, 128);
      while (size != -1 && size) {
        bdy.append(buff, size);
        size = read(pipe_fds[0], buff, 128);
      }
      if (size == -1) {
        std::cout << "unbale to read" << std::endl;
      }

      Body body = response.getBody();
      char *tmp;
      size = bdy.size();
      tmp = new char[bdy.size()];
      bdy.copy(tmp, size);
      body.setBody(tmp, size);
    }
  }
}
