//
//  main.cpp
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//


#include <iostream>
#include <string>

#include "zia/Listener.h"
#include "thread/Exception.h"
#include "EmbededObjectFactory.hpp"

int main(int argc, const char * argv[])
{
  EmbededObjectFactory objectFactory("modules");

    try {
    Listener a(8888);
    a.join();
    } catch (Thread::Exception e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
