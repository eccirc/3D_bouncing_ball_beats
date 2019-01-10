#ifndef BALLS_H
#define BALLS_H

#include "ofMain.h"


class balls
{

public:
    balls();

    //member functions
    void setupBall(ofPoint _loc, ofPoint _vel, ofPoint _mom, int _rad);
    void updateBall();
    void drawBall();

    //member variables
    ofPoint loc;
    ofPoint velocity;
    ofPoint mom;
    int radius;







};

#endif // BALLS_H
