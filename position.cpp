//
// Created by Einstein on 2019-04-28.
//

#include "position.h"
#include <iostream>

position::position()
{
    std::cout << "position constructor is called" << std::endl;
    *(x) = 0;
    *(x + 1) = 0;
}

position::~position()
{
    std::cout << "position destructor is called." << std::endl;
}

double* position::positionComponent()
{
    return x;
}

double* position::getPosition()
{
    return x;
}

void position::setPosition(double *position)
{
    *x = *position;
    *(x + 1) = *(position + 1);
}