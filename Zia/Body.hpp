#ifndef BODY_HPP__
#define BODY_HPP__ 1

#include <string>

namespace ZWE {
namespace HTTP {

class Body {
  protected:
    char * _buffer;
    size_t _size;

  public:
    size_t getSize() const;
    size_t append(char const &);
};

}}

#endif
