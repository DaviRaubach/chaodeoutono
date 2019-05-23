//
//  audioSetup.cpp
//  pdExample
//
//  Created by Davi Raubach Tuchtenhagen on 11/04/19.
//
//

#include "audioSetup.h"
#include "ofApp.h"

void audioSetup::setup() {
    
    ofSoundStream sound;
    auto devices = sound.getDeviceList();
    
    gui5.setup("select devices and click apply");
    gui5.setPosition(15, 30);
    gui5.setDefaultWidth(600);
    //gui5.add(inputsdev.setup(inputsdevstr));
    
    string devstr0 = ofToString(devices[0]);
    string devstr1 = ofToString(devices[1]);
    string devstr2 = ofToString(devices[2]);
    string devstr3 = ofToString(devices[3]);
    string devstr4 = ofToString(devices[4]);
    string devstr5 = ofToString(devices[5]);
    string devstr6 = ofToString(devices[6]);

    gui5.add(dif.setup(difstr, false));
    gui5.add(dev1i.setup(devstr0, false));
    gui5.add(dev2i.setup(devstr1, false));
    gui5.add(dev3i.setup(devstr2, false));
    gui5.add(dev4i.setup(devstr3, false));
    gui5.add(dev5i.setup(devstr4, false));
    gui5.add(dev6i.setup(devstr5, false));
    gui5.add(dev7i.setup(devstr6, false));
    //gui5.add(outputsdev.setup(outputsdevstr));
    gui5.add(dev1.setup(devstr0, false));
    gui5.add(dev2.setup(devstr1, false));
    gui5.add(dev3.setup(devstr2, false));
    gui5.add(dev4.setup(devstr3, false));
    gui5.add(dev5.setup(devstr4, false));
    gui5.add(dev6.setup(devstr5, false));
    gui5.add(dev7.setup(devstr6, false));
    gui5.add(applydevice.setup("apply"));
    applydevice.addListener(this, &audioSetup::applydeviceButtonPressed);
    

    
}

void audioSetup::update() {

    if(dif == true){difstr = "stereo";}
    else { difstr = "quadraphonic";}
}

void audioSetup::draw() {

    gui5.draw();
}


void audioSetup::applydeviceButtonPressed(){
    
    
    if (dev1 == true) {
        chosenOutDevice = 0;
    }
    if (dev2 == true) {
        chosenOutDevice = 1;
    }
    if (dev3 == true) {
        chosenOutDevice = 2;
    }
    
    if (dev4 == true) {
        chosenOutDevice = 3;
    }
    if (dev5 == true) {
        chosenOutDevice = 4;
    }
    if (dev6 == true) {
        chosenOutDevice = 5;
    }
    if (dev7 == true) {
        chosenOutDevice = 6;
    }
    
    if (dev1i == true) {
        chosenInDevice = 0;
    }
    if (dev2i == true) {
        chosenInDevice = 1;
    }
    if (dev3i == true) {
        chosenInDevice = 2;
    }
    if (dev4i == true) {
        chosenInDevice = 3;
    }
    if (dev5i == true) {
        chosenInDevice = 4;
    }
    if (dev6i == true) {
        chosenInDevice = 5;
    }
    if (dev7i == true) {
        chosenInDevice = 6;
    }
    
    if(dif == true) {
        nOutputs = 2;}
    else { nOutputs = 4;}
 
    ofRunApp(new ofApp());
    

}
void audioSetup::exit() {

    ofSoundStreamStop();
    applydevice.removeListener(this, &audioSetup::applydeviceButtonPressed);
    
}
