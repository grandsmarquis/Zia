
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

#include "../../trunk/apiheaders/ModuleInfos.h"
#include "../../trunk/apiheaders/Directives.h"
#include "../../trunk/apiheaders/DirectivesOrder.h"

#include "File.hpp"

int File::toto = 42;

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

void File::_getContentType(std::string & const path) {
  size_t pos = path.find_last_of('.');

  if (pos != string::npos) {
    std::string ext;

    ext = path.substr(pos);

  }
}

void File::_getEncoding(char *buff) {

  if (buff[0] == 0x3C && buff[1] != 0) {
    std::cout << "UTF-8" << std::endl;
  }

  printf("0x%X 0x%x\n", buff[0], buff[1]);
}

void File::callDirective(DirectivesOrder directiveorder, Request & request, Response & response)
{
  int length;
  char *buff;
  std::string path = "../www/index.html";
  std::ifstream resource(path.c_str(), std::ifstream::in);

  if (resource.is_open()) {
    if (resource.fail()) {
      std::cerr << "unable to read " << path << std::endl;
    } else {

      resource.seekg(0, std::ifstream::end);
      length = resource.tellg();
      resource.seekg(0, std::ifstream::beg);
      buff = new char[length];
      resource.read(buff, length);

      this->_getEncoding(buff);

      std::cout.write(buff, length);
    }
    resource.close();
  } else {
    std::cerr << "unable to open " << path << std::endl;
  }
}
