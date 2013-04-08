
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include <boost/filesystem.hpp>

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
  RequestHeader requestHeader = request.getHeader();

  // std::cout << requestHeader.getVersion() << std::endl;

  std::string script, query, uri = requestHeader.getArg(), pathInfo = boost::filesystem::current_path().native(), path = getenv("PATH");
  size_t pos = uri.find_first_of('?');

  if (pos == std::string::npos) {
    script = uri;
  } else {
    script = uri.substr(0, pos);
    query = uri.substr(pos + 1);
  }

  std::map<std::string, std::string> env;

  env["DOCUMENT_ROOT"] = "/mnt/hgfs/william/GitHub/jdourlens/Zia/modules/php";
  env["GATEWAY_INTERFACE"] = "CGI/1.1";
  env["HOME"] = "/home/SYSTEM";

  if (requestHeader.hasKey("Accept"))
    env["HTTP_ACCEPT"] = requestHeader.getValueForKey("Accept");

  if (requestHeader.hasKey("Accept-Encoding"))
    env["HTTP_ACCEPT_ENCODING"] = requestHeader.getValueForKey("Accept-Encoding");

  if (requestHeader.hasKey("Accept-Charset"))
    env["HTTP_ACCEPT_CHARSET"] = requestHeader.getValueForKey("Accept-Charset");

  if (requestHeader.hasKey("Accept-Language"))
    env["HTTP_ACCEPT_LANGUAGE"] = requestHeader.getValueForKey("Accept-Language");

  if (requestHeader.hasKey("Connection"))
    env["HTTP_CONNECTION"] = requestHeader.getValueForKey("Connection");

  if (requestHeader.hasKey("Host"))
    env["HTTP_HOST"] = requestHeader.getValueForKey("Host");

  if (requestHeader.hasKey("User-Agent"))
    env["HTTP_USER_AGENT"] = requestHeader.getValueForKey("User-Agent");

  env["PATH"] = path;
  // env["PATHEXT"] = ".COM;.EXE;.BAT;.CMD;.VBS;.VBE;.JS;.JSE;.WSF;.WSH;.MSC";
  env["PATH_INFO"] = pathInfo;
  env["PATH_TRANSLATED"] = pathInfo;
  env["QUERY_STRING"] = query;
  // env["REMOTE_ADDR"] = "127.0.0.1";
  // env["REMOTE_PORT"] = "63555";
  env["REQUEST_METHOD"] = requestHeader.getCommand();
  env["REQUEST_URI"] = requestHeader.getArg();
  env["SCRIPT_FILENAME"] = pathInfo + "/"  + script;
  env["SCRIPT_NAME"] = script;

  env["SERVER_ADDR"] = "127.0.0.1";
  env["SERVER_ADMIN"] = "(server admin's email address)";
  env["SERVER_NAME"] = "127.0.0.1";
  env["SERVER_PORT"] = "80";
  env["SERVER_PROTOCOL"] = requestHeader.getVersion();
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
