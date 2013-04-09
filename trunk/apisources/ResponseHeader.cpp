
#include <iostream>

#include "ResponseHeader.h"

ResponseHeader::ResponseHeader()
{
}

ResponseHeader::ResponseHeader(std::map<std::string, std::string> const & options, std::string const & statusCode, std::string const & statusMessage, std::string const & version)
  : _options(options), _statusCode(statusCode), _statusMessage(statusMessage), _version(version)
{
}

ResponseHeader::~ResponseHeader()
{
}

std::map<std::string, std::string> const & ResponseHeader::getOptions() const
{
  return _options;
}

std::string     const &         ResponseHeader::getStatusCode() const
{
  return (_statusCode);
}

std::string const &             ResponseHeader::getStatusMessage() const
{
  return (_statusMessage);
}

std::string const &             ResponseHeader::getValueForKey(std::string const & key) const
{
  return (_options.find(key)->second);
}

void ResponseHeader::setVersion(std::string const & version)
{
  _version = version;
}

std::string const &             ResponseHeader::getVersion() const
{
  return (_version);
}

void ResponseHeader::setValue(std::string const & headerAttribut, std::string const & value)
{
  this->_options[headerAttribut] = value;
}

void ResponseHeader::setStatusCode(std::string const & statusCode) {
  this->_statusCode = statusCode;
}


void ResponseHeader::setStatusMessage(std::string const & statusMessage) {
  this->_statusMessage = statusMessage;
}
