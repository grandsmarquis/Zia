
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
  return ((_options.find(key))->second());

}

std::string const &             ResponseHeader::getVersion() const
{
  return (_version);
}
