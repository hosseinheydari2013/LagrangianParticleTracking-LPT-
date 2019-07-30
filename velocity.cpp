//
// Created by Einstein on 2019-04-28.
//

#include "velocity.h"
#include <iostream>

velocity::velocity()
{
    std::cout << "velocity constructor is called" << std::endl;
    *(this->u) = 1;
    *(this->u + 1) = 1;
}

velocity::~velocity()
{
    std::cout << "velocity destructor is called." << std::endl;
}

double* velocity::velocityComponent()
{
    return this->u;
}