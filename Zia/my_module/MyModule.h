//
//  MyModule.h
//  Zia
//
//  Created by William Riancho on 12/02/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__MyModule__
#define __Zia__MyModule__

#include <iostream>

#include "../zia/AModule.h"
#include "MyModuleContextData.h"

class MyModule : public AModule {
private:
    int _len;
    std::string _sequence;
    
public:
    
    MyModule(t_module_identifier _identifier)
    :AModule(_identifier), _len(13), _sequence("°º¤ø,¸¸,ø¤º°`")
    {
        
    }
    
    virtual ~MyModule()
    {
        
    }
    
    virtual void initPackage(CrossModulePackage & package)
    {
        package.context[_moduleIdentifier] = new MyModuleContextData;
    }
    
    virtual void yield(CrossModulePackage & package)
    {
        // MyModuleContextData *context;
        
        // context = dynamic_cast<MyModuleContextData *>(package.context[_moduleIdentifier]);
        package.sock->Write(_sequence);
    }
};

#endif /* defined(__Zia__MyModule__) */
