# LagrangianParticleTracking-LPT-
**Simple Lagrangian Particle Tracking written in C++**

Currently, it has only solidBodyRotation implemented. The numerical integration for solidBodyRotation equations is done with RK3 (Runge-Kutta third order). Visualisation of the particles is done by using SFML (Simple and Fast Multimedia Library). The user is supposed to be able to correctly setup an environment with the aforementioned library. Exact solutions of solidBodyRotation equations can be found analytically. One needs to brush up his course on differential equations. Analytical solution is already added to the code, however, I might add later an explanation how those solutions are obtained.   

Note that SFML libraries are not added into this repo because I was not sure whether I can do it or not due to licensing issues. However, information on pre-compiled/source code versions of SFML can be found in "https://www.sfml-dev.org/download.php"

A sample Cmake instruction file (CMakeLists.txt) is provided for the users using it already. 

**Contributors**
- *Hosein Heidarifatasmi* (creator and holder of the repository)
