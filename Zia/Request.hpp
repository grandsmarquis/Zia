#ifndef REQUEST_HPP__
#define REQUEST_HPP__ 1

#include "RequestHeader.hpp"

namespace ZWE {
namespace HTTP {

class Request {
  protected:
    ZWE::HTTP::Request::Header _header;
    ZWE::HTTP::Body:: _body;

  public:
    ZWE::HTTP::Body const & getBody() const;
    ZWE::HTTP::Request::Header const & getHeader() const;
};

}}

#endif
