//Custom ball class

#include "balls.h"

balls::balls()
{

}
void balls::setupBall(ofPoint _loc, ofPoint _vel, ofPoint _mom, int _rad){

    //variables accessible to main app (can be randomised, for example)
    loc = _loc;
    velocity = _vel;
    mom = _mom;
    radius = _rad;


}
void balls::updateBall(){

    //classic bouncing ball stuff (thanks to ofBook for a refresher) - adapted for 3D

    loc.x += velocity.x;
    loc.y += velocity.y;
    loc.z -= velocity.z;

    velocity.x -= mom.x;
    velocity.y -= mom.y;
    velocity.z -= mom.z;

    //keep within the bounds of the 'box'
    if(loc.x >= ofGetWidth() - radius || loc.x <= 0 + radius){
        velocity.x *= -1;
    }
    if(loc.y >= ofGetHeight() - radius || loc.y <= 0 + radius){
        velocity.y *= -1;
    }
    if(loc.z >= 0  || loc.z <= -ofGetWidth()*2){
        velocity.z *= -1;
    }



}
void balls::drawBall(){


    ofDrawSphere(loc.x,loc.y,loc.z,radius);


}
