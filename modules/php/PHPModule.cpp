
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include <boost/filesystem.hpp>

#include "ModuleInfos.h"
#include "Directives.h"
#include "DirectivesOrder.h"

#include "ResponseHeader.h"

#include "HTTPParser.hpp"

#include "PHPModule.hpp"

#define EOL "\r\n"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
  __declspec(dllexport)
#endif

  ModuleInfos * get_module_infos()
  {
    ModuleInfos *m = new ModuleInfos;

    m->associatedDLL = "php";
    m->managedDirectives = CREATE_RESPONSE;
    m->managesHeaderOnly = true;
    m->name = "php";
    m->nbDirectives = 1;
    return (m);
  }

  Directives * get_directives()
  {
    return (new PHPModule());
  }

#ifdef __cplusplus
}
#endif


PHPModule::PHPModule()
{
}

PHPModule::~PHPModule()
{
}

void PHPModule::init()
{
}

const char ** PHPModule::buildEnv(RequestHeader & requestHeader) const
{
  std::map<std::string, std::string> env;
  std::string
    script,
    query,
    uri(requestHeader.getArg()),
    pathInfo(boost::filesystem::current_path().native() + "/www"),
    scriptFileName(pathInfo),
    home(getenv("HOME")),
    path(getenv("PATH"));
  size_t
    pos = uri.find_first_of('?'),
    size = uri.size();
  const char **e = new const char*[env.size() + 1];
  int i = 0;
  std::map<std::string, std::string>::iterator it;


  if (pos == std::string::npos) {
    script = uri;
  } else {
    script.append(uri.substr(0, pos).c_str(), pos);
    if (size && pos < size)
      query.append(uri.substr(pos + 1).c_str(), size - pos);
  }

  scriptFileName += script;

  env["DOCUMENT_ROOT"] = pathInfo;
  env["GATEWAY_INTERFACE"] = "CGI/1.1";
  env["HOME"] = home;

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
  // env["QUERY_STRING"] = query;

  // env["REMOTE_ADDR"] = "127.0.0.1";
  // env["REMOTE_PORT"] = "63555";
  // env["REQUEST_METHOD"] = requestHeader.getCommand();
  // env["REQUEST_URI"] = requestHeader.getArg();

  env["SCRIPT_FILENAME"] = scriptFileName;
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

  e = new const char*[env.size() + 1];

  for (it = env.begin(); it != env.end(); ++it) {
    std::string s(it->first + "=" + it->second);
    int size = s.size();
    char *buff  = new char[size + 1];
    s.copy(buff, size);
    buff[size] = 0;
    e[i] = buff;
    ++i;
  }
  e[i] = NULL;
  return e;
}

void PHPModule::callDirective(DirectivesOrder directiveorder, Request & request, Response & response, t_socket socket, struct sockaddr_in & connexionInfos)
{
  pid_t pid;
  int pipe_fds[2];

  pipe(pipe_fds);

  pid = fork();
  if (pid == -1) {
    std::cerr << "unable to fork" << std::endl;
  } else {
    if (pid == 0) {
      std::string bin("/usr/bin/php-cgi");
      const char *argv[] = {
        bin.c_str(),
        NULL
      };

      const char **env = this->buildEnv(request.getHeader());

      close(pipe_fds[0]);
      dup2(pipe_fds[1], 1);
      execve(bin.c_str(), const_cast<char * const*> (argv), const_cast<char * const*> (env));
      exit(1);
    } else {
      close(pipe_fds[1]);

      waitpid(pid, NULL, 0);

      ResponseHeader & responseHeader = response.getHeader();
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

      std::string header;
      std::string phpBody;

      size_t pos, last_pos;

      pos = bdy.find(EOL EOL);

      header = bdy.substr(0, pos);
      if (pos != std::string::npos) {
        phpBody = bdy.substr(pos + 4);

        Body & body = response.getBody();
        char *tmp;
        size = phpBody.size();

        tmp = new char[size];
        phpBody.copy(tmp, size);
        body.setBody(tmp, size);
      }

      last_pos = pos = 0;
      size_t line_pos;

      do{
        pos = header.find(EOL, last_pos);
        std::string line = header.substr(last_pos, pos - last_pos);

        line_pos = line.find(": ");
        std::string key(line.substr(0, line_pos));
        std::string value(line.substr(line_pos + 2));

        if (key == "Status") {
          size_t pos;

          pos = value.find_first_of(' ');
          responseHeader.setStatusCode(value.substr(0, pos));
          responseHeader.setStatusMessage(value.substr(pos + 1));
        } else {
          responseHeader.setValue(key, value);
        }

        last_pos = pos + 2;
      } while (std::string::npos != pos);

      if (responseHeader.getStatusCode().empty()) {
        responseHeader.setStatusCode("200");
        responseHeader.setStatusMessage("OK");
      }

      responseHeader.setVersion(request.getHeader().getVersion());

      response.assemble();
    }
  }
}
