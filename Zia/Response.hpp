#ifndef RESPONSE_HPP__
#define RESPONSE_HPP__ 1

namespace ZWE {
namespace HTTP {

class Response {
  protected:
    ZWE::HTTP::Response::Header _header;
    ZWE::HTTP::Body:: _body;

  public:
    ZWE::HTTP::Body & getBody();
    ZWE::HTTP::Request::Header & getHeader();
    char * serialize() const;
};

}}

#endif
