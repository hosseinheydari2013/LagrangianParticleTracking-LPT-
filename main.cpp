#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iomanip>
#include "particles.h"
#include "velocity.h"
#include "position.h"
#include "velocityField.h"
#include <fstream>
#include <vector>


int main() {
    std::cout << "Hello, World!" << std::endl;
    //- window settings
    sf::RenderWindow window( sf::VideoMode(1280, 960), "SFML");
    sf::CircleShape particleShape(100.f, 100.f); // particle for single motion - RK particle
    sf::CircleShape circularPath(100.f, 100.f); // particle for circular path - pure circular motion
    particleShape.setRadius(7.f);
    particleShape.setFillColor(sf::Color::Green);
    circularPath.setRadius(7.f);
    circularPath.setFillColor(sf::Color::Blue);
    sf::Time delay = sf::milliseconds(10);
    double margin = 400; // to keep particle inside display
    //- end of window settings

    //- array of particles
    std::vector<particles> cloud;
    double cloudPosition[2] = {100.0, 100.0};
    double cloudPosition1[2] = {130, 130};
    double cloudPosition2[2] = {160, 160};
    particles p3(cloudPosition);
    particles p4(cloudPosition1);
    particles p5(cloudPosition2);
    cloud.push_back(p3);
    cloud.push_back(p4);
    cloud.push_back(p5);

    std::vector<sf::CircleShape> cloudShape;
    sf::CircleShape c1(100.f, 100.f);
    sf::CircleShape c2(120.f, 120.f);
    sf::CircleShape c3(140.f, 140.f);
    c1.setRadius(7.f);
    c2.setRadius(7.f);
    c3.setRadius(7.f);
    c1.setFillColor(sf::Color::Green);
    c2.setFillColor(sf::Color::Red);
    c3.setFillColor(sf::Color::Yellow);
    cloudShape.push_back(c1);
    cloudShape.push_back(c2);
    cloudShape.push_back(c3);

    std::vector<double> px0_cloud = {*(const_cast<double*>(cloud[0].position())), *(const_cast<double*>(cloud[1].position()))
    , *(const_cast<double*>(cloud[2].position()))};
    std::vector<double> py0_cloud = {*(const_cast<double*>(cloud[0].position() + 1)), *(const_cast<double*>(cloud[1].position() + 1))
    , *(const_cast<double*>(cloud[2].position() + 1))};

    //- using vector iterators
    //typedef std::vector<particles>::iterator cloudIter;
    //typedef std::vector<sf::CircleShape>::iterator cloudShapeIter;

    //- end of array of particles

    double particleVelocity[2] = {2, 3};
    double particleDiameter = 0.001;
    double particleDensity = 1000;
    double particlePosition[2] = {0, 0};
    double initialPosition[2] = {100.0, 100.0};
    float omega = 2;

    particles p1(particleDiameter, particleVelocity, particlePosition, particleDensity);
    std::cout << "particle position is: [ " << *(p1.position()) << ", " << *(p1.position() + 1) << " ]" <<
              std::endl;

    // now we move the particle
    p1.move();

    std::cout << "new particle position is: [ " << *(p1.position()) << ", " << *(p1.position() + 1) << " ]" <<
              std::endl;

    velocity objVel; //- empty constructor is called
    position objPos; //- empty constructor is called
    objPos.setPosition(const_cast<double*>(p1.position())); //- setting position WRT particle position

    p1.setVelocity(solidBodyRotation(objVel, objPos, omega));
    std::cout << "new particle velocity is: [ " << *(p1.velocity()) << ", " << *(p1.velocity() + 1) << " ]" <<
              std::endl;

    float time = 0.0;
    double delta_t = 0.001; // used for solidBodyRotation && RK method
    particles p2(initialPosition); //- initial particle position
    double px0 = *(const_cast<double*>(p2.position()));
    double py0 = *(const_cast<double*>(p2.position() + 1));

    //- test area

    int counter = 0;

    // writing it to a text file
    /*
    std::ofstream file_;
    file_.open("particleDynamcis.txt");
    file_ << "   particle position" << std::setw(50) << "       particle velocity" << std::endl;
    file_.precision(7);
    */

    //- solving a coupled system of ode with Third-order Runge-Kutta method
        // note that solution updates has to go in while loop of window to be shown in graphics

    std::vector<double>* timeVector = new std::vector<double>; // time vector only needed for RK method.
    (*timeVector).resize(10000); // x and y values are gonna be calculated at these intervals u and v will be f and g!
    for(int i = 0; i < (*timeVector).size(); i++)
    {
        (*timeVector)[i] = i * delta_t;
    }

    std::vector<double>* xVector = new std::vector<double>;
    (*xVector).resize(10000);
    (*xVector)[0] = initialPosition[0]; // setting initial x position of the particle

    std::vector<double>* yVector = new std::vector<double>;
    (*yVector).resize(10000);
    (*yVector)[0] = initialPosition[1]; // setting initial y posiiton of the particle

    rungeKutta(*xVector, *yVector, *timeVector, initialPosition, omega, delta_t);

        //- Error calculation for RK WRT analytical solution of solidBodyRotation
        std::vector<double>* xerrorVector  = new std::vector<double>;
        (*xerrorVector).reserve(10000);

        std::vector<double>* yerrorVector  = new std::vector<double>;
        (*yerrorVector).reserve(10000);
    //- end of solving a coupled system of ode with Third-order Runge-Kutta method


    //- circular motion
    static double angle = 0;
    double radius = 50;
    double currentPosition[2] = {0, 0};
    //- end of circular motion


    // writing error data to a file
    std::ofstream errorData;
    errorData.open("errorData.txt");
    if(!errorData.is_open())
    {
        std::cout << "file could not be created or opened." << std::endl;
        exit(2); // terminate the program with error code 2
    }
    //errorData << "Time(s)" << "    " << "position_x(m)" << "    " << "position_y(m)" << std::endl;


    while(window.isOpen())
    {
        sf::Event event;

        while ( window.pollEvent(event) )
        {
            //- closing the window with x
            if(event.type == sf::Event::Closed)
                window.close();

            //- closing the window with Escape key pressed
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        //- single particle motion

        solidBodyRotation(p2, px0, py0, time, delta_t, omega); //- move the particle with analytical solution
        particleShape.setPosition(*(p2.position()) + margin, *(p2.position() + 1) + margin);

        //- particle cloud motion
/*
        for(std::pair<cloudIter, cloudShapeIter> i(cloud.begin(), cloudShape.begin());
        i.first != cloud.end();
        ++i.first, ++i.second)
        {
            px0 = *(const_cast<double*>((*(i.first)).position()));
            py0 = *(const_cast<double*>((*(i.first)).position() + 1));
            solidBodyRotation(*(i.first), px0, py0, time, delta_t, omega);
            (*(i.second)).setPosition(*((*(i.first)).position()) + margin, *((*(i.first)).position() + 1) + margin);

            window.draw(*(i.second));
        }
*/
        //- clear the display
        window.clear();

        //- update particle velocity and position fields [currently using analytical solution]
        for(int i = 0; i < cloud.size(); i++)
        {
            //px0_cloud[i] =  *(const_cast<double*>(cloud[i].position())); // updating px0 for next particle in the cloud
            //py0_cloud[i] =  *(const_cast<double*>(cloud[i].position() + 1)); // updating py0 for next particle in the cloud
            solidBodyRotation(cloud[i], px0_cloud[i], py0_cloud[i], time, delta_t, omega); // updating cloud position
            cloudShape[i].setPosition( *(cloud[i].position()) + margin, *(cloud[i].position() + 1) + margin); // assign cloud position to cloudShape

            //- draw particles
            window.draw(cloudShape[i]);

        }

            //- particle motion with Runge-Kutta
                if(counter < (*timeVector).size())
                {
                    particleShape.setPosition((*xVector)[counter] + margin, (*yVector)[counter] + margin);
                    window.draw(particleShape);
                    //- calculate error
                    (*xerrorVector)[counter] = *(cloud[0].position()) - (*xVector)[counter]; // (analytical - RK) / analytical
                    (*yerrorVector)[counter] = *(cloud[0].position() + 1) - (*yVector)[counter]; // (analytical - RK) / analytical
                    errorData << (*timeVector)[counter] << "    " << (*xerrorVector)[counter] << "    " << (*yerrorVector)[counter] << std::endl;

                    counter++;
                }
            //- end of particle motion with Runge-Kutta

            //- particle motion on circular path
            circularRotation(angle, initialPosition, radius, currentPosition);
            circularPath.setPosition(currentPosition[0], currentPosition[1]);
            window.draw(circularPath);
            //- end of particle motion on circular path

        //- end of particle cloud motion

        time += delta_t; //- increment time
        angle += 0.1;

        //- display the window and draw objects
        window.draw(particleShape);
        window.display();
        sf::sleep(delay);

    }

    errorData.close();

    delete  yVector;
    delete  xVector;
    delete  timeVector;
    delete xerrorVector;
    delete yerrorVector;
    return 0;
}