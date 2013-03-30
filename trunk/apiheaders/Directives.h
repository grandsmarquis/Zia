#ifndef __DIRECTIVES_H__
#define __DIRECTIVES_H__

#include <iostream>

#include "Request.h"
#include "Response.h"
#include "DirectivesOrder.h"

class Directives
{
public:
	virtual ~Directives() {
    std::cout << "destruct directives" << std::endl;
  };
	virtual	void	callDirective(DirectivesOrder directiveorder, Request & request) = 0;
	virtual	void	callDirective(DirectivesOrder directiveorder, Response & response) = 0;
	virtual	void	init() = 0;
};


#endif // !_DIRECTIVES_H_
