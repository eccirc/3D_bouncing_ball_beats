/*This is my playful take on the algorithmic drum machine
 * from Mick Grierson's AAVP class.
 * credit to Mick Grierson and Maximilliam https://github.com/micknoise/Maximilian
 * and the ofBook for a refresher on OOP - the example of which I adapted and
 * made to work with a '3D' environment.
 *
 * David Williams January 2019
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);

    //sample set switches
    set1 = true;
    set2 = false;

    //weird momentum triggers
    noiseX = false;
    noiseY = false;
    noiseZ = false;



    //ball class setup
    /*first value = inital ball location
     * second value = initial ball velocity
     * third value = initial ball momentum (alter this if you want velocity to change over time)
     * fourth value = initial ball radius
     *
     */

    ball.setupBall(ofPoint(ofGetWidth()/2,ofGetHeight()/2,0), ofPoint(ofRandom(1,40),ofRandom(1,50),ofRandom(1,50)), ofPoint(0,0,0), 100);


    //load sample etc. before setting up soundcard

    //for loading samples in Maxim use the full path
    //sample set one
    kick.load("PATH/TO/YOUR/SAMPLES");
    snare.load("PATH/TO/YOUR/SAMPLES");
    hatCls.load("PATH/TO/YOUR/SAMPLES");
    hatOpn.load("PATH/TO/YOUR/SAMPLES");
    cowBell.load("PATH/TO/YOUR/SAMPLES");
    tom.load("PATH/TO/YOUR/SAMPLES");
    //sample set two
    BD.load("PATH/TO/YOUR/SAMPLES");
    CL.load("PATH/TO/YOUR/SAMPLES");
    Conga.load("/PATH/TO/YOUR/SAMPLES");
    Clave.load("PATH/TO/YOUR/SAMPLES");
    Cym1.load("PATH/TO/YOUR/SAMPLES");
    Cym2.load("PATH/TO/YOUR/SAMPLES");


    //This is the necessary audio setup stuff for running Maxim with OF
    //Get and print a list of possible output devices
    auto devices = soundStream.getDeviceList();
    //cout << devices << endl;
    //This is the working setup for OF 0.10.0
    ofSoundStreamSettings settings;

    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.sampleRate = 44100;
    settings.bufferSize = 512;
    settings.numBuffers = 2;
    settings.setOutListener(this);
    settings.setOutDevice(devices[5]);
    soundStream.setup(settings);



}
//--------------------------------------------------------------
void ofApp::update(){
    ball.updateBall();


   //an example of some of the weird effects you can get by adjusting the momentum...
    nSeed += 0.001;
    float n;

    //X dimension
    if(noiseX){
        n = ofSignedNoise(nSeed) * 5;
        ball.mom.x = n;
        cout << "noiseX on"<<endl;
    }
    else{
        ball.mom.x = 0;
        cout<<"noiseX off"<<endl;
    }
    //Y dimension
    if(noiseY){
        n = ofSignedNoise(nSeed) * 5;
        ball.mom.y = n;
        cout << "noiseY on"<<endl;
    }
    else{
        ball.mom.y = 0;
        cout << "noiseY off" << endl;
    }
    //Z dimension
    if(noiseZ){
        n = ofSignedNoise(nSeed) * 5;
        ball.mom.z = n;
        cout <<"noiseZ on"<<endl;
    }
    else{
        ball.mom.z = 0;
        cout<<"noiseZ off"<<endl;
    }



}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackgroundGradient(ofColor::black, ofColor::white, OF_GRADIENT_CIRCULAR);

    ofPushStyle();
    ofNoFill();

    hitCalcs();

    //ball class (easy to grab co-ord data from)
    ofSetSphereResolution(5);
    ball.drawBall();
    ofPopStyle();


    //Create the inner receding 'box'
    ofPushStyle();
    ofNoFill();
    ofSetColor(255);
    float z = - ofGetWidth()*2;

   ofDrawRectangle(0,0,z, ofGetWidth(), ofGetHeight());

   ofSetLineWidth(2);

   ofDrawLine(0,0,0, 0,0, z);
   ofDrawLine(0,ofGetHeight(),0,0,ofGetHeight(),z);
   ofDrawLine(ofGetWidth(),0,0,ofGetWidth(),0,z);
   ofDrawLine(ofGetWidth(),ofGetHeight(),0,ofGetWidth(),ofGetHeight(),z);
   ofPopStyle();




}
//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &outBuffer){


    //Put all sound related code within this for loop (This setup for OF 0.10.0)
    for(size_t i = 0; i < outBuffer.getNumFrames(); i ++){


        hitCalcs();
        if(set1){
        //trigger the samples
        if(hcT == 1){hatCls.trigger();}
        if(sT == 1){snare.trigger();}
        if(kT ==1){kick.trigger();}
        if(hoT ==1){hatOpn.trigger();}
        if(cT ==1){cowBell.trigger();}
        if(tT ==1){tom.trigger();}

        //add samples to an output

        hatCout = hatCls.playOnce();
        snareOut = snare.playOnce();
        kickOut = kick.playOnce();
        hatOout = hatOpn.playOnce();
        cowOut = cowBell.playOnce();
        tomOut = tom.playOnce();

        mixOut = snareOut + kickOut + hatCout + hatOout + tomOut + cowOut;
        }
        if(set2){
            if(hcT == 1){Clave.trigger();}
            if(sT == 1){CL.trigger();}
            if(kT ==1){BD.trigger();}
            if(hoT ==1){Conga.trigger();}
            if(cT ==1){Cym1.trigger();}
            if(tT ==1){Cym2.trigger();}

            //add samples to an output

            ClaveOut = Clave.playOnce();
            ClapOut = CL.playOnce();
            BDout = BD.playOnce();
            CongaOut = Conga.playOnce();
            Cym1Out = Cym1.playOnce();
            Cym2Out = Cym2.playOnce();

            mixOut = ClaveOut + ClapOut + BDout + CongaOut + Cym1Out + Cym2Out;
        }




        //These are the audio stereo outs
        outBuffer.getSample(i, 0) = mixOut;
        outBuffer.getSample(i, 1) = mixOut;









    }

}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    //click the right mouse button to start a new ball with different velocity settings
    if(button){
        ball.velocity = ofPoint(ofRandom(1,50),ofRandom(1,50),ofRandom(1,50));
        ball.loc = ofPoint(x,y,0);
    }

}

//tweak the triggers here - currenty set to correspond roughly with each of the six 'walls' of the receding cube
void ofApp::hitCalcs(){
    //set ball drum triggers
    //hat closed
    if(ball.loc.x >= ofGetWidth() - ball.radius){
        hcT = 1;
        //cout << "hat close" << endl;
        ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255));
    }
    else{hcT = 0;}

    //hat open
    if(ball.loc.x <= 0 + ball.radius){
        hoT = 1;
        //cout<<"hat open"<<endl;
        ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255));
    }
    else{hoT = 0;}
    //kick
    if(ball.loc.y >= ofGetHeight() - ball.radius){
        kT = 1;
        //cout<<"kick"<<endl;
        ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255));
    }
    else{ kT =0;}
    //snare
    if(ball.loc.y <= 0 + ball.radius){
        sT =1;
        //cout <<"snare"<<endl;
        ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255));
    }
    else{sT = 0;}
    //cowbell
    if(ball.loc.z >= 0 ){
        cT = 1;
        //cout << "cow" << endl;
        ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255));
    }
    else{cT =0;}
    //tom
    if(int(ball.loc.z) <= -ofGetWidth()*2 + ball.radius){
        tT = 1;
        //cout << "tom"<< endl;
        ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255));

    }
    else{tT = 0;}



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    //toggle the sample sets
    if(key == '1'){
        set1 = true;
        set2 = false;
    }
    if(key == '2'){
        set1 = false;
        set2 = true;
    }

    //toggle the wonky noise momentum
    if(key == 'x'){
        noiseX = !noiseX;
    }
    if(key == 'y'){
        noiseY = !noiseY;
    }
    if(key == 'z'){
        noiseZ = !noiseZ;
    }
}
