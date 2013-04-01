#ifndef __DIRECTIVES_H__
# define	__DIRECTIVES_H__

#include "Request.h"
#include "Response.h"
#include "DirectivesOrder.h"

class Directives
{
public:
	virtual ~Directives() {};
	virtual	void	callDirective(DirectivesOrder directiveorder, Request & request, Response & response) = 0;
	virtual	void	init() = 0;
};


#endif // !_DIRECTIVES_H_
