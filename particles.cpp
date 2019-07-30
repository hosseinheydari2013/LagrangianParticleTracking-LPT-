//
// Created by Einstein on 2019-04-23.
//

#include "particles.h"

// constructors
particles::particles()
{
    this->d_ = 0.001;
    *(this->p_) = 0;
    *(this->p_ + 1) = 0;
    this->rho_ = 1000;
    *(this->U_) = 0;
    *(this->U_ + 1) = 0;
    this->stepFraction_ = 0.2;
    this->timeStep_ = 0.1;
}

particles::particles(double &particleDiameter, double* particleVelocity, double* particlePosition,
                     double &particleDensity)
                     {
                         this->d_ = particleDiameter;
                         *(this->p_) = *particlePosition;
                         *(this->p_ + 1) = *(particlePosition + 1);
                         this->rho_ = particleDensity;
                         *(this->U_) = *particleVelocity;
                         *(this->U_ + 1) = *(particleVelocity + 1);
                         this->stepFraction_ = 0.2;
                         this->timeStep_ = 0.1;
                     }
//- destructors
particles::~particles(){}

particles::particles(double* initialPosition)
{
    *(this->p_) = *initialPosition;
    *(this->p_ + 1) = *(initialPosition + 1);

}

void particles::calculateForce()
{

}

double particles::mass()
{
    return double(this->rho_ * 3.1415 * powf(this->d_, 2) / 6.0);
}

const double* particles::position() const
{
    return this->p_;
}

const double* particles::velocity() const
{
    return this->U_;
}

double particles::diameter() const
{
    return this->d_;
}

double particles::density() const
{
    return this->rho_;
}

void particles::setVelocity(double *u)
{
    *(this->U_) = *(u);
    *(this->U_ + 1) = *(u + 1);
}

void particles::setVelocity(double& ux, double& uy)
{
    *(this->U_) = ux;
    *(this->U_ + 1) = uy;
}

void particles::setPosition(double *p)
{
    *(this->p_) = *(p);
    *(this->p_) = *(p + 1);
}

void particles::setPosition(double& xComponent, double& yComponent)
{
    *(this->p_) = xComponent;
    *(this->p_ + 1) = yComponent;
}

void particles::move()
{
    *(this->p_) = *(this->U_) * this->timeStep_;
    *(this->p_ + 1) = *(this->U_ + 1) * this->timeStep_;
}