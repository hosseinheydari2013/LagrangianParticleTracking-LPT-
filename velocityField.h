//
// Created by Einstein on 2019-04-28.
//

#ifndef LPT_VELOCITYFIELD_H
#define LPT_VELOCITYFIELD_H

//- This file is responsible for calculation of the velocity field && position of particles with different methods

double* solidBodyRotation(velocity& velocity, position& position, float& omega)
{
    *(velocity.velocityComponent()) = - omega * *(position.positionComponent() + 1);
    *(velocity.velocityComponent() + 1) = omega * *(position.positionComponent());
    return velocity.velocityComponent();
}

void solidBodyRotation(particles& p, double& px0, double& py0, float& time, float& dt, float& omega)
{
    double xComponent = px0 * std::cosf(omega * time) - py0 * std::sinf(omega * time);
    double yComponent = px0 * std::sinf(omega * time) + py0 * std::cosf(omega * time);
    double ux = - yComponent * omega ;
    double uy = xComponent * omega;

    p.setPosition(xComponent, yComponent); //- updates particle position
    p.setVelocity(ux, uy);
}

void solidBodyRotation(particles& p, double& px0, double& py0, float& time, double& dt, float& omega)
{
    double xComponent = px0 * std::cos(omega * time) - py0 * std::sin(omega * time);
    double yComponent = px0 * std::sin(omega * time) + py0 * std::cos(omega * time);
    double ux = - yComponent * omega ;
    double uy = xComponent * omega;

    p.setPosition(xComponent, yComponent); //- updates particle position
    p.setVelocity(ux, uy);
}

void circularRotation(double& angle, double* initialPosition, double& radius, double* currentPosition)
{
    currentPosition[0] = cos(angle) * radius;
    currentPosition[1] = sin(angle) * radius;
    currentPosition[0] += 100;
    currentPosition[1] +=  100;
}

//- Third order Runge-Kutta implementation

double dxdt (double t, double x, double y, float& omega)
{
    return -omega * y;
}

double dydt(double t, double x, double y, float& omega)
{
    return omega * x;
}

double dxdt (double t, double x, double y)
{
    return -2 * y;
}

double dydt(double t, double x, double y)
{
    return 2 * x;
}

//- calculation functions for Runge-Kutta method

double f(const double& x, const double& y, const double& t, const float& omega) // this is the general case f(x, y, t) f->u g->v
{
    return -(double)omega * y; // form of the function will change based on the velocity function
}

double g(const double& x, const double& y, const double& t, const float& omega)
{
    return (double)omega * x; // form of the function will change based on the velocity function
}

void rungeKutta(std::vector<double>& xVector, std::vector<double>& yVector, std::vector<double>& timeVector, double* initialPosition, float& omega, double& delta_t)
{
    for(int i = 0 ; i < timeVector.size(); i++)
    {
        double F1 = f(initialPosition[0], initialPosition[1], timeVector[i], omega) * delta_t;
        double G1 = g(initialPosition[0], initialPosition[1], timeVector[i], omega) * delta_t;
        double x1 = initialPosition[0] + (delta_t / 2.0) * F1;
        double x2 = initialPosition[1] + (delta_t / 2.0) * G1;
        double t1 = timeVector[0] + delta_t / 2.0;
        double F2 = f(x1, x2, t1, omega) * delta_t;
        double G2 = g(x1, x2, t1, omega) * delta_t;
        double x3 = initialPosition[0] + (3.0 / 4.0) * F2;
        double x4 = initialPosition[1] + (3.0 / 4.0) * G2;
        double t2 = timeVector[0] + delta_t * (3.0 / 4.0);
        double F3 = f(x3, x4, t2, omega) * delta_t;
        double G3 = g(x3, x4, t2, omega) * delta_t;
        xVector[i + 1] = xVector[i] + (1.0 / 9.0) * (2.0 * F1 + 3.0 * F2 + 4.0 * F3);
        yVector[i + 1] = yVector[i] + (1.0 / 9.0) * (2.0 * G1 + 3.0 * G2 + 4.0 * G3);
        initialPosition[0] = xVector[i + 1];
        initialPosition[1] = yVector[i + 1];
    }

}



#endif //LPT_VELOCITYFIELD_H
