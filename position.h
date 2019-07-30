//
// Created by Einstein on 2019-04-28.
//

#ifndef LPT_POSITION_H
#define LPT_POSITION_H


class position {

private:
    //- private variables
    double x[2];

public:
    //- constructors
    position();

    //- destructors
    ~position();

    //- member functions
    double* positionComponent();
        //- setters
    void setPosition(double* position);

        //- getters
    double* getPosition();

protected:

};


#endif //LPT_POSITION_H
