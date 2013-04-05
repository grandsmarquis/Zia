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
	  if (tmp)
	    _arg = tmp;
	  tmp = strtok(NULL, " ");
	  if (tmp)
	    _version = tmp;
	  state += 1;
	}
      else if (state == 1 && tmp)
	{
	  tmp = strtok(_tmp, ":");
	  one = tmp;
	  tmp2 = strtok(NULL, "\n");
	  if (!one.empty() && tmp2)
	    {
	      two = tmp2;
	      _map[one] = two;
	    }
	  else
	    {
	      _body = ss.str();
	    }
	}
      else
	{
	  state += 1;
	}
    }
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

std::string const &HTTPParser::getBody() const
{
  return (_body);
}

std::map<std::string, std::string> const &HTTPParser::getMap() const
{
  return (_map);
}
