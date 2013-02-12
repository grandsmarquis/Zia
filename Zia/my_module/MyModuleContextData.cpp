//
//  MyModuleContextData.cpp
//  Zia
//
//  Created by William Riancho on 12/02/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#include "MyModuleContextData.h"

MyModuleContextData::MyModuleContextData()
:_i(0)
{
  
}

MyModuleContextData::~MyModuleContextData()
{
  
}

const int MyModuleContextData::getI()
{
  return _i;
}

void MyModuleContextData::setI(int i)
{
  _i = i;
}
