#ifndef __MODULEINFOS_H__
# define __MODULEINFOS_H__

#include "DirectivesOrder.h"

struct ModuleInfos {
	std::string	associatedDLL;
	char				managedDirectives;
	bool				managesHeaderOnly;
	std::string	name;
	int					nbDirectives;
};

#endif // !_MODULEINFOS_H_
