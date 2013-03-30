#ifndef __MODULEINFOS_H__
# define __MODULEINFOS_H__

struct ModuleInfos {
	std::string	const	associatedDLL;
	char				managedDirectives;
	bool				mangesHeaderOnly;
	std::string	const	name;
	int					nbDirectives;
};

#endif // !_MODULEINFOS_H_
