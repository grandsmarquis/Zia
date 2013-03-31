#include "HTTPParser.hpp"

HTTPParser::HTTPParser(char *buffer, int size)
{
  int state = 0;
  buffer[size - 1] = 0;
  std::stringstream ss(buffer);
  char _tmp[255];
  char *tmp;
  char *tmp2;
  std::string one, two;

  while (ss.good())
    {
      ss.getline(_tmp, 255);
      if (state == 0) 
	{
	  tmp = strtok(_tmp, " ");
	  _cmd = tmp;
	  tmp = strtok(NULL, " ");
	  _arg = tmp;
	  tmp = strtok(NULL, " ");
	  _version = tmp;
	  state += 1;
	}
      else if (state == 1 && tmp)
	{
	  tmp = strtok(_tmp, ":");
	  one = tmp;
	  tmp2 = strtok(NULL, "\n");
	  if (tmp2)
	    {
	      two = tmp2;
	      _map[one] = two;
	    }
	}
      else
	{
	  state += 1;
	}
    }
  std::cout << "::" << _cmd << "::" << _arg << "::" << _version <<std::endl;
  for(std::map<std::string, std::string>::iterator it = _map.begin(); it!= _map.end(); ++it) {
    std::cout << it->first << " ::: " << it->second << std::endl;
  }
}

void HTTPParser::parseHeader(char *buffer, int size)
{
}

void HTTPParser::parseBody(char *buffer, int size)
{
}

std::string const &HTTPParser::getArg() const
{
  return (_arg);
}

std::string const &HTTPParser::getCmd() const
{
  return (_cmd);
}

std::string const &HTTPParser::getVersion() const
{
  return (_version);
}

std::map<std::string, std::string> const &HTTPParser::getMap() const
{
  return (_map);
}
