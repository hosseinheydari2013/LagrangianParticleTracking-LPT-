//
// Created by Einstein on 2019-04-23.
//

#ifndef LPT_PARTICLES_H
#define LPT_PARTICLES_H

#include <cmath>

class particles {

private:
    double d_; // particle diameter
    double U_[2]; // particle velocity
    double p_[2]; // particle position
    double rho_; // particle density
    double stepFraction_; // lagrangian sub time-stepping
    double timeStep_; // Eulerian time step

public:

    //- member functions
    void move(); // to move the particles around with respect to continuous phase velocity distribution
    void calculateForce(); // to calculate forces on the particle from the continuous phase
    double mass();
    const double* position() const;
    const double* velocity() const;
    double density() const;
    double diameter() const;
    void setVelocity(double* u);
    void setVelocity(double& ux, double& uy);
    void setPosition(double* p);
    void setPosition(double& xComponent, double& yComponent);



    //- constructors
    particles();
    particles(double& particleDiameter, double* particleVelocity, double* particlePosition,
            double& particleDensity);
    particles(double* initialPosition);

    //- destructors
    ~particles();
protected:

};


#endif //LPT_PARTICLES_H
