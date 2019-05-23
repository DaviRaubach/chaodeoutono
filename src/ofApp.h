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
#include "ofxXmlSettings.h"
#include <algorithm>



// a namespace for the Pd types
using namespace pd;


// inherit pd receivers to receive message and midi events
class ofApp : public ofBaseApp, public PdReceiver, public PdMidiReceiver {

	public:

		// main
		void setup();
		void update();
		void draw();
		void exit();
		
        void applydevButtonPressed();
        void loadallButtonPressed();
        void difToggle(bool & pressed);

		// input callbacks
		void keyPressed(int key);
		
		// audio callbacks
		void audioReceived(float * input, int bufferSize, int nChannels);
		void audioRequested(float * output, int bufferSize, int nChannels);
		
		// pd message receiver callbacks
		void print(const std::string& message);
		
		void receiveBang(const std::string& dest);
		void receiveFloat(const std::string& dest, float value);
		void receiveSymbol(const std::string& dest, const std::string& symbol);
		void receiveList(const std::string& dest, const List& list);
		void receiveMessage(const std::string& dest, const std::string& msg, const List& list);
    
		
		// pd midi receiver callbacks
		void receiveNoteOn(const int channel, const int pitch, const int velocity);
		void receiveControlChange(const int channel, const int controller, const int value);
		void receiveProgramChange(const int channel, const int value);
		void receivePitchBend(const int channel, const int value);
		void receiveAftertouch(const int channel, const int value);
		void receivePolyAftertouch(const int channel, const int pitch, const int value);
		
		void receiveMidiByte(const int port, const int byte);
    
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
        void sleepcp(int milliseconds) {
        clock_t time_end;
        time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
        while (clock() < time_end)
        {
        }
        }
    
    
        void myWait(float *floatWait);
    
        bool bHide;
        bool bHideother;

        bool bFirst;
    
    unsigned long actualTime, sucessTimer;
    unsigned int sucessTimeDelta;
    
    
    ofxGuiGroup gui2;
    ofxToggle dsp;
    ofxButton loadall;
    ofParameterGroup nois;
    
    ofParameter<float> input;
    ofParameter<float> amplitude;
    ofParameter<float> threshold;
    ofParameter<float> ctrlmic;
    ofParameter<float> headmic;
    ofParameter<float> HPheadmic;
    
    
    ofxGuiGroup gui3;
    ofParameter<float> output;
    
    //bool difusion;
    //string difusionstring;
    ofxToggle rev;
    ofParameter<float> revwet;
    ofParameter<float> revdry;
    ofxToggle spat;

    ofxGuiGroup gui4;
    ofxButton programs;
    ofParameter<string> progstring;
    ofxLabel progs;
    //string progstring;
   // string progstring2;
    
    
    ofxGuiGroup audiosetup;
    ofxToggle audioset;
    ofxToggle instruct;

    
    
    
    ofxGuiGroup gui5;
    

    ofxLabel outputsdev;
    ofParameter<string> outputsdevstr;
    ofParameterGroup outputdevices;

    ofParameter<bool> dev1;
    ofParameter<bool> dev2;
    ofParameter<bool> dev3;
    ofParameter<bool> dev4;
    ofParameter<bool> dev5;
    ofParameter<bool> dev6;
    ofParameter<bool> dev7;
    ofxLabel inputsdev;
    ofParameter<string> inputsdevstr;
    
    ofParameterGroup inputdevices;
    ofParameter<bool> dev1i;
    ofParameter<bool> dev2i;
    ofParameter<bool> dev3i;
    ofParameter<bool> dev4i;
    ofParameter<bool> dev5i;
    ofParameter<bool> dev6i;
    ofParameter<bool> dev7i;
    
    ofParameter<bool> dif;
    ofParameter<string> difstr;
    ofxButton applydev;
    ofxLabel difL;
    
    ofxGuiGroup dspCpu;
    ofParameter<float> fdspCpu;

        ofParameter<ofColor> color;
        ofParameter<bool> filled;
    
        ofxButton ringButton;
        ofParameter<string> screenSize;
    
        //ofxPanel gui;
    

		ofxPd pd;
		vector<float> scopeArray;
		vector<Patch> instances;
    
        ofImage image;
        string typeStr;
    
        ofTrueTypeFont  franklinBook14;
        ofTrueTypeFont  franklinBook32;

    
        float amplit;
		int midiChan;
    
    int amplint;
    int amplint2;
    int amplint3;
    int amplint4;
    int amplitudeelectro;
    
    //int cpuFpd;
    int nInputs;
    int nOutputs;
    int intsel;
    
    int ticksPerBuffer;
    
    //ofSoundStream soundStream;
    
    ofSoundStream sound;
    ofSoundStreamSettings settings;
    vector<ofSoundDevice> devices;
    string devicesstr;
    
    //vector<string> names;
    
   
   
    int chosenOutDevice;
    int chosenInDevice;
  

    
    float VUx;
    float VUy;
    float VUn;
    float VUx2;
    float VUn2;
    float VUx3;
    float VUn3;
    float VUx4;
    float VUn4;
    float lvspaX;
    float lvspaY;
    float flspaX;
    float flspaY;
    
    float cpuFpd;
    float cpuFpdW;

    
    string cpu;
    
    std::string out_string;
    std::stringstream ss;
    
    
    
};


