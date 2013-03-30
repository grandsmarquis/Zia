#ifndef __MODULE_INFOS_HPP__
#define __MODULE_INFOS_HPP__ 1

#include <string>

class ModuleInfos {
  protected:
    std::string const & associteDLL;
    char manageDirectives;
    bool managesHeaderOnly;
    std::string const & name;
    int nbDirectives;
};

#endif
