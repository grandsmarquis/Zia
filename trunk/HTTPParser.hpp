#ifndef __HTTP_PARSER_HH__
#define __HTTP_PARSER_HH__

#include <string>
#include <iostream>
#include <sstream>

#include <map>

#include <stdio.h>
#include <cstring>

class HTTPParser
{
public:
  HTTPParser(char *buffer, int bufferLenght);

  std::string const &getArg() const;
  std::string const &getCmd() const;
  std::string const &getVersion() const;
  std::string const &getBody() const;
  std::map<std::string, std::string> const &getMap() const;

private:
  std::string _arg;
  std::string _cmd;
  std::string _version;
  std::map<std::string, std::string> _map;
  std::string _body;

};

#endif
