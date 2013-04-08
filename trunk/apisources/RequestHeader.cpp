
#include <iostream>
#include "RequestHeader.h"

RequestHeader::RequestHeader()
{
}

RequestHeader::RequestHeader (std::map<std::string, std::string> const & options, std::string const & arg, std::string const & command, std::string const & version)
  :  _arg(arg), _command(command), _options(options), _version(version)
{
}

RequestHeader::~RequestHeader ()
{
}

std::string const &RequestHeader::getArg() const
{
  return (_arg);
}

std::string const &RequestHeader::getCommand() const
{
  return (_command);
}

std::string const &RequestHeader::getValueForKey(std::string const & key) const
{
  return (_options.find(key)->second);
}

std::string const &RequestHeader::getVersion() const
{
  return (_version);
}

bool RequestHeader::hasKey(std::string const & value)
{
  return (_options.find(value) != _options.end());
}

void RequestHeader::setCommand(std::string const & command)
{
  _command = command;
}

void RequestHeader::setArg(std::string const &arg)
{
  _arg = arg;
}

void RequestHeader::setVersion(std::string const & version)
{
  _version = version;
}

void RequestHeader::setValue(std::string const & key, std::string const & value)
{
  _options[key] = value;
}
