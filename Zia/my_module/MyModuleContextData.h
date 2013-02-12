//
//  MyModuleContextData.h
//  Zia
//
//  Created by William Riancho on 12/02/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#ifndef __Zia__MyModuleContextData__
#define __Zia__MyModuleContextData__

#include <iostream>

#include "../zia/IModuleContextData.h"

class MyModuleContextData : public IModuleContextData
{
private:
  int _i;
  
public:
  MyModuleContextData();
  virtual ~MyModuleContextData();
  const int getI();
  void setI(int i);
};


#endif /* defined(__Zia__MyModuleContextData__) */
