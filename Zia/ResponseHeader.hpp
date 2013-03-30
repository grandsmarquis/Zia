#ifndef RESPONSE_HEADER_HPP__
#define RESPONSE_HEADER_HPP__ 1

#include <cstdint>

#include <string>
#include <map>

namespace ZWE {
namespace HTTP {

typedef enum {
  v_0_9,
  v_1_0,
  v_1_1
} version;

typedef uint16_t status_code;

typedef enum {
  GET, HEAD, POST, PUT, DELETE,
  TRACE, OPTIONS, CONNECT, PATCH
} method;

namespace Response {

class Header {

  protected:
    ZWE::HTTP::status_code _statusCode;
    ZWE::HTTP::version _version;
    std::map<std::string, std::string> _headers;

  public:
    ZWE::HTTP::status_code getStatusCode() const;
    void setStatusCode(ZWE::HTTP::status_code);

    ZWE::HTTP::version getVersion() const;
    void setVersion(ZWE::HTTP::version);

    bool hasHeader() const;

    std::string const & getHeader(std::string const &) const;
    void setHeader(std::string const &);

};

}}}

#endif
