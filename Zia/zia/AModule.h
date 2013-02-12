//
//  AModule.h
//  Zia
//
//  Created by William Riancho on 12/02/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__AModule__
#define __Zia__AModule__

#include <iostream>

#include "CrossModulePackage.h"
#include "api.h"

class AModule {
protected:
    t_module_identifier _moduleIdentifier;
    
public:
    AModule(t_module_identifier identifier);
    
    virtual ~AModule();
    virtual void initPackage(CrossModulePackage & _context) = 0;
    virtual void yield(CrossModulePackage & _context) = 0;
};

#endif /* defined(__Zia__AModule__) */
