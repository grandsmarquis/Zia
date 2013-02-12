//
//  CrossModulePackage.h
//  Zia
//
//  Created by William Riancho on 12/02/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__CrossModulePackage__
#define __Zia__CrossModulePackage__

#include <iostream>
#include <map>

#include "api.h"
#include "../net/Socket.h"
#include "IModuleContextData.h"

class CrossModulePackage {
public:
    Net::Socket *sock;
    std::map<t_module_identifier, IModuleContextData *> context;
    
     CrossModulePackage(Net::Socket * sock);
    ~CrossModulePackage();
};

#endif /* defined(__Zia__CrossModulePackage__) */
