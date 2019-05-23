/*
 * Copyright (c) 2011 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxPd for documentation
 *
 */


#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPd.h"
#include <sstream>
#include <vector>
#include "time.h"



// a namespace for the Pd types
using namespace pd;


// inherit pd receivers to receive message and midi events
class audioSetup : public ofBaseApp {
    
public:
    
    // main
    void setup();
    void update();
    void draw();
    void exit();
    
    void applydeviceButtonPressed();
    
    int nInputs;
    int nOutputs;
    int intsel;
    
    int ticksPerBuffer;
    
    //ofSoundStream soundStream;
    

    
    int chosenOutDevice;
    int chosenInDevice;
    
    ofParameter<string> difstr;

    
    ofxGuiGroup gui5;
    //ofxLabel outputsdev;
    //string outputsdevstr = "select 1 output device";
    ofxToggle dif;
    
    ofxToggle dev1;
    ofxToggle dev2;
    ofxToggle dev3;
    ofxToggle dev4;
    ofxToggle dev5;
    ofxToggle dev6;
    ofxToggle dev7;
    
    //ofxLabel inputsdev;
    //string inputsdevstr = "select 1 input devices";
    ofxToggle dev1i;
    ofxToggle dev2i;
    ofxToggle dev3i;
    ofxToggle dev4i;
    ofxToggle dev5i;
    ofxToggle dev6i;
    ofxToggle dev7i;
    ofxButton applydevice;
    
    

    
};
