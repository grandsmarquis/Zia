//
//  main.cpp
//  Zia
//
//  Created by William Riancho on 29/01/13.
//  Copyright (c) 2013 William Riancho. All rights reserved.
//

#include <iostream>
#include "net/TCPSocket.h"
#include "net/Exception.h"

int main(int argc, const char * argv[])
{
    try {
    Net::TCPSocket sock(8889);
    
    sock.Listen();
    // insert code here...
    sock.Accept();
    } catch (Net::Exception e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "Hello, World!\n";
    return 0;
}
