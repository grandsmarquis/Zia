#ifndef __REQUEST_HEADER_HPP__
#define __REQUEST_HEADER_HPP__ 1

#include <string>
#include <map>

namespace ZWE {
namespace HTTP {
namespace Request {

class Header {

  protected:
    ZWE::HTTP::method _method;
    std::string _resource; // "/wiki/Main_Page
    ZWE::HTTP::version _version;
    std::map<std::string, std::string> _headers; // [ { "Host", "en.wikipedia.org" } ]

  public:
    ZWE::HTTP::method getMethod() const;
    void setMethod(ZWE::HTTP::method);

    std::string const & getResource() const;
    void setResource(std::string const &);

    ZWE::HTTP::version getVersion() const;
    void setVersion(ZWE::HTTP::version);

    bool hasHeader() const;

    std::string const & getHeader(std::string const &) const;
    void setHeader(std::string const &);

};

}}}


#endif
