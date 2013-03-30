#ifndef __DIRECTIVES_H__
# define	__DIRECTIVES_H__

#include "Request.h"
#include "Response.h"
#include "DirectivesOrder.h"

class Directives
{
public:
	virtual ~Directives() {};
	virtual	void	callDirective(DirectivesOrder directiveorder, Request & request);
	virtual	void	callDirective(DirectivesOrder directiveorder, Response & response);
	virtual	void	init();
};


#endif // !_DIRECTIVES_H_
