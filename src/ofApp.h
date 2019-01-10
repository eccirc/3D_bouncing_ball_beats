#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "balls.h"


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    //seperate the distance calculation stuff
    void hitCalcs();

    //These are the necessary's for setting up Maxim in OF
    //This is the setup for OF 0.10.0 (See 'Sound' exaples in the examples directory for more detailed setup
            void audioOut(ofSoundBuffer &outBuffer);
            //setup ofSoundStream
            ofSoundStream soundStream;


/*Some basic Maxim objects:  maxiOsc osc; maxiFilter filter; maxiClock clock; maxiEnv env; maxiSample sample*/
    //PUT MAXIM OBJECTS HERE

    //sample hits to correspond with each of the 6 'walls'
    //sample set one
    maxiSample kick;
    maxiSample snare;
    maxiSample hatCls;
    maxiSample hatOpn;
    maxiSample cowBell;
    maxiSample tom;
    //sample set two
    maxiSample BD;
    maxiSample CL;
    maxiSample Conga;
    maxiSample Clave;
    maxiSample Cym1;
    maxiSample Cym2;





    //PUT OTHER STUFF HERE

    //booleans for loading different sample sets
    bool set1, set2;

    //some other bools to trigger some weird stuff
    bool noiseX, noiseY, noiseZ;
    float nSeed;

    //simple 'on' 'off' triggers for the samples
    int kT,sT,hcT, hoT, cT, tT;

    //Outputs

    double kickOut,snareOut, hatCout, hatOout, cowOut, tomOut;

    double BDout, ClapOut, CongaOut, ClaveOut, Cym1Out, Cym2Out;

    double oscOut, mixOut;

    balls ball;









};
