#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    ofSetDataPathRoot("../Resources/data/");
    franklinBook14.load("frabk.ttf", 10, false);
    franklinBook14.setLineHeight(18.0f);
    franklinBook14.setLetterSpacing(1.037);
    franklinBook32.load("frabk.ttf", 32, false);
    
	ofSetFrameRate(50);
    ofSetVerticalSync(true);
    
	ofSetLogLevel("Pd", OF_LOG_VERBOSE); // see verbose info inside
    
    cout << "alou" << endl;
    
    VUx = 50;
    VUy = 630;
    VUx2 = VUx + 30;
    VUx3 = VUx + 60;
    VUx4 = VUx + 90;
   
    bHide = false;
    bHideother = false;
	// double check  where we are ...
	cout << ofFilePath::getCurrentWorkingDirectory() << endl;
    devices = sound.getDeviceList();

    
    devicesstr = ofToString("Select input and output devices, apply and reopen the program. \n") + ofToString(devices[0])
    + "\n" + ofToString(devices[1])
    + "\n" + ofToString(devices[2])
    + "\n" + ofToString(devices[3])
    + "\n" + ofToString(devices[4])
    + "\n" + ofToString(devices[5])
    + "\n" + ofToString(devices[6]);
    
    //nois.add(input.set("input", 0, 0, 100));
    
    
    gui2.setup("inputs");
    gui2.setPosition(15, 50);
    gui2.setWidthElements(300);
    //gui2.add(nois);
    gui2.add(loadall.setup("load initial parameters"));
    loadall.addListener(this, &ofApp::loadallButtonPressed);
    gui2.add(input.set("input", 0, 0, 100));
    gui2.add(amplitude.set("input amplitude", 0, -101, 6 ));
    gui2.add(threshold.set("threshold", 0, -101, 6 ));
    gui2.add(ctrlmic.set("out ctrl mic", 0, 0, 1));
    gui2.add(headmic.set("out headjoint mic", 0, 0, 1));
    gui2.add(HPheadmic.set("hipass headjoint mic", 0, 0, 1000));
    
    
    gui2.loadFromFile( "settings.xml" );
    
    gui3.setup("outputs");
    gui3.setPosition(15, 240);
    gui3.setWidthElements(300);
    
    gui3.add(output.set("output", 0, 0, 3));
    gui3.add(dsp.setup("DSP", false));
   // difusion = true;
    gui3.add(revwet.set("reverb wet", 0, 0, 1));
    gui3.add(revdry.set("reverb dry", 0, 0, 1));
    gui3.add(spat.setup("spatialization on/off", true));
    
    gui3.loadFromFile( "settings.xml" );
    
    gui4.setup("programs");
    gui4.setPosition(15, 380);
    gui4.setWidthElements(300);
    //gui4.add(programs.setup(""));
    gui4.add(progs.setup(progstring));
    gui4.loadFromFile( "settings.xml" );

    
    audiosetup.setup();
    audiosetup.setPosition(15, 430);
    audiosetup.add(audioset.setup("audio settings", false));
    audiosetup.add(instruct.setup("instructions", false));
    audiosetup.loadFromFile( "settingsshows.xml" );

    
//    

    
    
    
    inputdevices.setName("inputs");
    inputdevices.add(dev1i.set("in 0", false));
    
    inputdevices.add(dev2i.set("in 1", false));
    inputdevices.add(dev3i.set("in 2", false));
    inputdevices.add(dev4i.set("in 3", false));
    inputdevices.add(dev5i.set("in 4", false));
    inputdevices.add(dev6i.set("in 5", false));
    inputdevices.add(dev7i.set("in 6", false));
    
    
    outputdevices.setName("outputs");
    outputdevices.add(dev1.set("out 0", false));
    outputdevices.add(dev2.set("out 1", false));
    outputdevices.add(dev3.set("out 2", false));
    outputdevices.add(dev4.set("out 3", false));
    outputdevices.add(dev5.set("out 4", false));
    outputdevices.add(dev6.set("out 5", false));
    outputdevices.add(dev7.set("out 6", false));
    
    gui5.setup("select devices");
    gui5.setPosition(250, 400);
    gui5.setDefaultWidth(200);
    gui5.add(inputdevices);
    gui5.add(outputdevices);
    gui5.add(dif.set("difusion", true));
    dif.addListener(this, &ofApp::difToggle);
    gui5.add(difL.setup(difstr));
    gui5.add(applydev.setup("apply and exit"));
    applydev.addListener(this, &ofApp::applydevButtonPressed);
    
    gui5.loadFromFile( "settingsgui5.xml" );
    
    fdspCpu.set("cpu", 0, 0, 100);
    dspCpu.setup();
    dspCpu.setPosition(15, 700);
    dspCpu.add(fdspCpu);

    
    // the number of libpd ticks per buffer,
    // used to compute the audio buffer len: tpb * blocksize (always 64)
#ifdef TARGET_LINUX_ARM
    // longer latency for Raspberry PI
    int ticksPerBuffer = 32; // 32 * 64 = buffer len of 2048
    int numInputs = 0; // no built in mic
#else
    int ticksPerBuffer = 8; // 8 * 64 = buffer len of 512
    int numInputs = 2;
#endif
    
    
    // setup OF sound stream
    if (dev1 == true) {
        settings.setOutDevice(devices[0]);
    }
    if (dev2 == true) {
        settings.setOutDevice(devices[1]);
    }
    if (dev3 == true) {
        settings.setOutDevice(devices[2]);
    }
    
    if (dev4 == true) {
        settings.setOutDevice(devices[3]);
    }
    if (dev5 == true) {
        settings.setOutDevice(devices[4]);
    }
    if (dev6 == true) {
        settings.setOutDevice(devices[5]);
    }
    if (dev7 == true) {
        settings.setOutDevice(devices[6]);
    }
    
    if (dev1i == true) {
        settings.setInDevice(devices[0]);
    }
    if (dev2i == true) {
        settings.setInDevice(devices[1]);
    }
    if (dev3i == true) {
        settings.setInDevice(devices[2]);
    }
    if (dev4i == true) {
        settings.setInDevice(devices[3]);
    }
    if (dev5i == true) {
        settings.setInDevice(devices[4]);
    }
    if (dev6i == true) {
        settings.setInDevice(devices[5]);
    }
    if (dev7i == true) {
        settings.setInDevice(devices[6]);
    }
    
    if(dif == true) {
        nOutputs = 2;
    difstr = "stereo";}
    else { nOutputs = 4;
        difstr = "quadraphonic";
    }
    
    nInputs = 2;
    
    
    sucessTimeDelta = 2000;
    
    
    //#ifdef TARGET_LINUX
    //    // Latest linux versions default to the HDMI output
    //    // this usually fixes that. Also check the list of available
    //    // devices if sound doesn't work
    //    auto devices = soundStream.getMatchingDevices("default");
    //    if(!devices.empty()){
    //        settings.setOutDevice(devices[0]);
    //    }
    //#endif
    
    settings.numInputChannels = nInputs;
    settings.numOutputChannels = nOutputs;
    settings.sampleRate = 44100;
    settings.bufferSize = ofxPd::blockSize() * ticksPerBuffer;
    settings.setInListener(this);
    settings.setOutListener(this);
    

    
    
    
    
    
    
    //cout << ofToString(devices[2].inputChannels) << endl;
    //cout << devices[2] << endl;
    
    //    Stream or buffer under/overflow means that you are sending not enough/too many samples to your sound card. You don’t have that much control over this aside from trying not doing too much audio processing at any one time.
    //
    //    The most common is the stream underflow…this means that the system wasn’t able to feed the sound card buffers with enough data, meaning that there is a interruption in the stream (which usually translates as a pop or click in your speakers). Generally I think this is caused by the CPU being too busy processing stuff, or perhaps bad drivers. You can avoid this by having good hardware (integrated sound cards in the motherboard are usually bad), and up to date drivers. Also look up information on how to optimise your system for audio. It is operating system dependent, but generally involves removing background processes and tweaking other system settings.
    //
    //        Overflow is when you are sending too much data to the sound card and it’s buffers have to drop data because it can’t keep up.
    
    
    //    deviceBt = false;
    
    //    gui = new ofxUISuperCanvas("Select Devices");
    //    gui->setPosition(200, 200);
    //    gui->addSpacer();
    //    names = {"1", "2", "3"};
    //    ddl = gui->addDropDownList("Select Output Device", names);
    //    ddl->setAllowMultiple(true);
    //    ddl->setAutoClose(true);
    //    ddl2 = gui->addDropDownList("Select Input Device", names);
    //    ddl2->setAllowMultiple(true);
    //    ddl2->setAutoClose(true);
    //
    //    gui->autoSizeToFitWidgets();
    //
    //    gui->addButton("Apply", deviceBt);
    //    //    gui->setDrawWidgetPadding(true);
    //    ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent);
    
    
    // setup Pd
    //
    // set 4th arg to true for queued message passing using an internal ringbuffer,
    // this is useful if you need to control where and when the message callbacks
    // happen (ie. within a GUI thread)
    //
    // note: you won't see any message prints until update() is called since
    // the queued messages are processed there, this is normal
    //
    if(!pd.init(2, numInputs, 44100, ticksPerBuffer, false)) {
        OF_EXIT_APP(1);
    }
    
    // audio processing on
    pd.start();
    
    
    
    midiChan = 1; // midi channels are 1-16
    
    // subscribe to receive source names
    
    pd.subscribe("ampli");
    pd.subscribe("amplifluteFpd");
    pd.subscribe("ampliout1Fpd");
    pd.subscribe("ampliout2Fpd");
    pd.subscribe("ampliout3Fpd");
    pd.subscribe("ampliout4Fpd");
    pd.subscribe("spatleavesXFpd");
    pd.subscribe("spatleavesYFpd");
    pd.subscribe("spatfluteXFpd");
    pd.subscribe("spatfluteYFpd");
    pd.subscribe("cpuFpd");

    
    
    
    // add message receiver, required if you want to recieve messages
    pd.addReceiver(*this); // automatically receives from all subscribed sources
    //pd.ignoreSource(*this, "env");        // don't receive from "env"
    //pd.ignoreSource(*this);             // ignore all sources
    //pd.receiveSource(*this, "toOF");	  // receive only from "toOF"
    
    // add midi receiver, required if you want to recieve midi messages
    //pd.addMidiReceiver(*this); // automatically receives from all channels
    //pd.ignoreMidiChannel(*this, 1);     // ignore midi channel 1
    //pd.ignoreMidiChannel(*this);        // ignore all channels
    //pd.receiveMidiChannel(*this, 1);    // receive only from channel 1
    
    // add the data/pd folder to the search path
    pd.addToSearchPath("pd/abs");
    
    
    
    
    // open patch
    Patch patch = pd.openPatch("pd/chaodeoutono.pd");
    cout << patch << endl;
    
    
    
    

    // -----------------------------------------------------
	
	// stream interface
	//pd << Bang("fromOF")
	//<< Float("fromOF", 100)
	//<< Symbol("fromOF", "test string");

	// send a list
	//pd.startMessage();
	//pd.addFloat(1.23);
	//pd.addSymbol("a symbol");
	//pd.finishList("fromOF");

	// send a message to the $0 receiver ie $0-fromOF
	//pd.startMessage();
	//pd.addFloat(1.23);
	//pd.addSymbol("a symbol");
	//pd.finishList(patch.dollarZeroStr()+"-fromOF");

	// send a list using the List object
	//List testList;
	//testList.addFloat(1.23);
	//testList.addSymbol("sent from a List object");
	//pd.sendList("fromOF", testList);
	//pd.sendMessage("fromOF", "msg", testList);

	// stream interface for list
	//pd << StartMessage() << 1.23 << "sent from a streamed list" << FinishList("fromOF");

	//cout << "FINISH Message Test" << endl;

	// -----------------------------------------------------
	//cout << endl << "BEGIN MIDI Test" << endl;

	// send functions
//    pd.sendNoteOn(midiChan, 60);
//	pd.sendControlChange(midiChan, 0, 64);
//	pd.sendProgramChange(midiChan, 100);    // note: pgm num range is 1 - 128
//	pd.sendPitchBend(midiChan, 2000);   // note: ofxPd uses -8192 - 8192 while [bendin] returns 0 - 16383,
										// so sending a val of 2000 gives 10192 in pd
//	pd.sendAftertouch(midiChan, 100);
//	pd.sendPolyAftertouch(midiChan, 64, 100);
//	pd.sendMidiByte(0, 239);    // note: pd adds +2 to the port number from [midiin], [sysexin], & [realtimein]
//	pd.sendSysex(0, 239);       // so sending to port 0 gives port 2 in pd
//	pd.sendSysRealTime(0, 239);
//
//	// stream
//	pd << NoteOn(midiChan, 60) << ControlChange(midiChan, 100, 64)
//	   << ProgramChange(midiChan, 100) << PitchBend(midiChan, 2000)
//	   << Aftertouch(midiChan, 100) << PolyAftertouch(midiChan, 64, 100)
//	   << StartMidi(0) << 239 << Finish()
//	   << StartSysex(0) << 239 << Finish()
//	   << StartSysRealTime(0) << 239 << Finish();
//
//	cout << "FINISH MIDI Test" << endl;

	// -----------------------------------------------------
//	cout << endl << "BEGIN Array Test" << endl;
//
//	// array check length
//	cout << "array1 len: " << pd.arraySize("array1") << endl;
//    
//
//	// read array
//	std::vector<float> array1;
//	pd.readArray("array1", array1);	// sets array to correct size
//	cout << "array1 ";
//	for(int i = 0; i < array1.size(); ++i)
//		cout << array1[i] << " ";
//	cout << endl;
//
//	// write array
//	for(int i = 0; i < array1.size(); ++i)
//		array1[i] = i;
//	pd.writeArray("array1", array1);
//
//	// ready array
//	pd.readArray("array1", array1);
//	cout << "array1 ";
//	for(int i = 0; i < array1.size(); ++i)
//		cout << array1[i] << " ";
//	cout << endl;
//
//	// clear array
//	pd.clearArray("array1", 10);
//
//	// ready array
//	pd.readArray("array1", array1);
//	cout << "array1 ";
//	for(int i = 0; i < array1.size(); ++i)
//		cout << array1[i] << " ";
//	cout << endl;
//
//	cout << "FINISH Array Test" << endl;
//
//	// -----------------------------------------------------
//	cout << endl << "BEGIN PD Test" << endl;
//
//	pd.sendSymbol("fromOF", "test");
//
//	cout << "FINISH PD Test" << endl;
//
//	// -----------------------------------------------------
//	cout << endl << "BEGIN Instance Test" << endl;
//
//	// open 10 instances
//	for(int i = 0; i < 10; ++i) {
//		Patch p = pd.openPatch("pd/instance.pd");
//		instances.push_back(p);
//	}
//
//	// send a hello bang to each instance individually using the dollarZero
//	// to [r $0-instance] which should print the instance dollarZero unique id
//	// and a unique random number
//	for(int i = 0; i < instances.size(); ++i) {
//		pd.sendBang(instances[i].dollarZeroStr()+"-instance");
//	}
//
//	// send a random float between 0 and 100
//	for(int i = 0; i < instances.size(); ++i) {
//		pd.sendFloat(instances[i].dollarZeroStr()+"-instance", int(ofRandom(0, 100)));
//	}
//
//	// send a symbol
//	for(int i = 0; i < instances.size(); ++i) {
//		pd.sendSymbol(instances[i].dollarZeroStr()+"-instance", "howdy dude");
//	}
//
//	// close all instances
//	for(int i = 0; i < instances.size(); ++i) {
//		pd.closePatch(instances[i]);
//	}
//	instances.clear();
//
//	cout << "FINISH Instance Test" << endl;
//
//	// -----------------------------------------------------
//	// play a tone by sending a list
//	// [list tone pitch 72 (
//	pd.startMessage();
//	pd.addSymbol("pitch");
//	pd.addFloat(72);
//	pd.finishList("tone");
//	pd.sendBang("tone");
    
}

//--------------------------------------------------------------
void ofApp::update() {
    
    
	// since this is a test and we don't know if init() was called with
	// queued = true or not, we check it here
	if(pd.isQueued()) {
		// process any received messages, if you're using the queue and *do not*
		// call these, you won't receieve any messages or midi!
		pd.receiveMessages();
		pd.receiveMidi();
	}
    
    
    
    
	// update scope array from pd
	//pd.readArray("scope", scopeArray);
    
    
    //GUI2
    pd.sendFloat("dspFof", dsp);
    pd.sendFloat("loadFof", loadall);
    pd.sendFloat("inputFof", input);
    // amplitude só recebe
    pd.sendFloat("thresholdFof", threshold);
    pd.sendFloat("ctrlmicFof", ctrlmic);
    pd.sendFloat("headmicFof", headmic);
    pd.sendFloat("HPheadmicFof", HPheadmic);

    //GUI3
    
    pd.sendFloat("outputFof", output);
    //pd << Float("outputFof", output);

    pd.sendFloat("difFof", dif);
    pd.sendFloat("revFof", rev);
    pd.sendFloat("revwetFof", revwet);
    pd.sendFloat("revdryFof", revdry);
    pd.sendFloat("spatFof", spat);

    //GUI4
    //pd.sendFloat("programsBFof", programs);

    //VUs
    VUn = amplint - 101;
    VUn2 = amplint2 - 101;
    VUn3 = amplint3 - 101;
    VUn4 = amplint4 - 101;
    
    
    amplitudeelectro = 10;
    //ss << cpuFpd;
    //out_string = ss.str();
    //cpu = out_string;

    
    amplitudeelectro = (amplint + amplint2)/2;
    
    actualTime = ofGetElapsedTimeMillis();
    
    if (actualTime - sucessTimer > sucessTimeDelta) {
        cpuFpdW = cpuFpd;    }
    
    
}


//--------------------------------------------------------------
void ofApp::draw() {
    ofBackgroundGradient(ofColor::gray, ofColor::black);
    
    
    //Draw flute and leaves spatialization
    ofEnableAlphaBlending();
    ofSetColor(180, 180, 180, 127);
    ofDrawCircle(lvspaX, lvspaY, amplitudeelectro);
    ofSetColor(255, 255, 255);
    ofDrawCircle(lvspaX, lvspaY, 10);


    ofEnableAlphaBlending();
    ofSetColor(180, 180, 180, 127);
    ofDrawCircle(flspaX, flspaY, ((amplitude/4)) );
    ofSetColor(0, 0, 0);
    ofDrawCircle(flspaX, flspaY, 10);
    
    
   

    

    
	// draw //
    //ofSetColor(0, 0, 0, 127);
    //ofSetColor(255, 255, 255);
	//ofSetRectMode(OF_RECTMODE_CENTER);
	//float x = 0, y = ofGetHeight()/11;
	//float w = ofGetWidth() / (float) scopeArray.size()/4, h = ofGetHeight();
	//for(int i = 0; i < scopeArray.size()-1; ++i) {
	//	ofDrawLine(x, y+scopeArray[i]*h, x+w, y+scopeArray[i+1]*h);
	//	x += w;
	//}
    
    float w = ofGetWidth();
    float h = ofGetHeight();
   
    
    
    
    
    
    
    
    if( !bHide ){
        
        
    ofSetColor(255, 255, 255);
    franklinBook14.drawString("Autumn Ground", 10, 25);
    
        

    
     
        
    
    
        
    
    
//    ofFill ();
//    ofSetColor(255, 255, 255);
//    ofDrawBitmapString(difstr, 400, 290);
    
//    ofFill ();
//    ofSetColor(255, 255, 255);
//
//    franklinBook32.drawString(progstring, 125, 450);

    
       
    ofFill();
        ofEnableAlphaBlending();
    ofSetColor(100,100,100, 127);
    ofDrawRectangle(VUx - 10 ,VUy - 110, 150, 140);
    
        //VU1
    ofFill();
    if (VUn >= -99){
        ofSetColor(66,244,66);
        ofDrawRectangle(VUx,VUy,20,7);
    }
    ofFill();
    if (VUn >= -75){
        ofSetColor(66,244,66);
        ofDrawRectangle(VUx,VUy - 10,20,7);
        
    }
    ofFill();
    if (VUn >= -50){
        ofSetColor(104,244,66);
        ofDrawRectangle(VUx,VUy - 20,20,7);
        
    }
    ofFill();
    if (VUn >= -35){
        ofSetColor(104,244,66);
        ofDrawRectangle(VUx,VUy - 30,20,7);
        
    }
    ofFill();
    if (VUn >= -24){
        ofSetColor(200,244,66);
        ofDrawRectangle(VUx,VUy - 40,20,7);
    }
    
    ofFill();
    if (VUn >= -18){
        ofSetColor(200,244,66);
        ofDrawRectangle(VUx,VUy - 50,20,7);
        
    }
    ofFill();
    if (VUn >= -14){
        ofSetColor(244,241,66);
        ofDrawRectangle(VUx,VUy - 60,20,7);
        
    }
    ofFill();
    if (VUn >= -12){
        ofSetColor(244,241,66);
        ofDrawRectangle(VUx,VUy - 70,20,7);
        
    }
    ofFill();
    if (VUn >= -6){
        ofSetColor(244,191,66);
        ofDrawRectangle(VUx,VUy - 80,20,7);
        
    }
    ofFill();
    if (VUn >= -3){
        ofSetColor(244,191,66);
        ofDrawRectangle(VUx,VUy - 90,20,7);
        
    }
    
    ofFill();
    if (VUn >= 0){
        ofSetColor(244,66,66);
        ofDrawRectangle(VUx,VUy - 100,20,15);
        
    }
    
    
    
    // VU2
    ofFill();
    if (VUn2 >= -99){
        ofSetColor(66,244,66);
        ofDrawRectangle(VUx2,VUy,20,7);
    }
    ofFill();
    if (VUn2 >= -75){
        ofSetColor(66,244,66);
        ofDrawRectangle(VUx2,VUy - 10,20,7);
        
    }
    ofFill();
    if (VUn2 >= -50){
        ofSetColor(104,244,66);
        ofDrawRectangle(VUx2,VUy - 20,20,7);
        
    }
    ofFill();
    if (VUn2 >= -35){
        ofSetColor(104,244,66);
        ofDrawRectangle(VUx2,VUy - 30,20,7);
        
    }
    ofFill();
    if (VUn2 >= -24){
        ofSetColor(200,244,66);
        ofDrawRectangle(VUx2,VUy - 40,20,7);
    }
    
    ofFill();
    if (VUn2 >= -18){
        ofSetColor(200,244,66);
        ofDrawRectangle(VUx2,VUy - 50,20,7);
        
    }
    ofFill();
    if (VUn2 >= -14){
        ofSetColor(244,241,66);
        ofDrawRectangle(VUx2,VUy - 60,20,7);
        
    }
    ofFill();
    if (VUn2 >= -12){
        ofSetColor(244,241,66);
        ofDrawRectangle(VUx2,VUy - 70,20,7);
        
    }
    ofFill();
    if (VUn2 >= -6){
        ofSetColor(244,191,66);
        ofDrawRectangle(VUx2,VUy - 80,20,7);
        
    }
    ofFill();
    if (VUn2 >= -3){
        ofSetColor(244,191,66);
        ofDrawRectangle(VUx2,VUy - 90,20,7);
        
    }
    
    ofFill();
    if (VUn2 >= 0){
        ofSetColor(244,66,66);
        ofDrawRectangle(VUx2,VUy - 100,20,15);
        
    }
    
    // VU3
    ofFill();
    if (VUn3 >= -99){
        ofSetColor(66,244,66);
        ofDrawRectangle(VUx3,VUy,20,7);
    }
    ofFill();
    if (VUn3 >= -75){
        ofSetColor(66,244,66);
        ofDrawRectangle(VUx3,VUy - 10,20,7);
        
    }
    ofFill();
    if (VUn3 >= -50){
        ofSetColor(104,244,66);
        ofDrawRectangle(VUx3,VUy - 20,20,7);
        
    }
    ofFill();
    if (VUn3 >= -35){
        ofSetColor(104,244,66);
        ofDrawRectangle(VUx3,VUy - 30,20,7);
        
    }
    ofFill();
    if (VUn3 >= -24){
        ofSetColor(200,244,66);
        ofDrawRectangle(VUx3,VUy - 40,20,7);
    }
    
    ofFill();
    if (VUn3 >= -18){
        ofSetColor(200,244,66);
        ofDrawRectangle(VUx3,VUy - 50,20,7);
        
    }
    ofFill();
    if (VUn3 >= -14){
        ofSetColor(244,241,66);
        ofDrawRectangle(VUx3,VUy - 60,20,7);
        
    }
    ofFill();
    if (VUn3 >= -12){
        ofSetColor(244,241,66);
        ofDrawRectangle(VUx3,VUy - 70,20,7);
        
    }
    ofFill();
    if (VUn3 >= -6){
        ofSetColor(244,191,66);
        ofDrawRectangle(VUx3,VUy - 80,20,7);
        
    }
    ofFill();
    if (VUn3 >= -3){
        ofSetColor(244,191,66);
        ofDrawRectangle(VUx3,VUy - 90,20,7);
        
    }
    
    ofFill();
    if (VUn3 >= 0){
        ofSetColor(244,66,66);
        ofDrawRectangle(VUx3,VUy - 100,20,15);
        
    }
    // VU4
    ofFill();
    if (VUn4 >= -99){
        ofSetColor(66,244,66);
        ofDrawRectangle(VUx4,VUy,20,7);
    }
    ofFill();
    if (VUn4 >= -75){
        ofSetColor(66,244,66);
        ofDrawRectangle(VUx4,VUy - 10,20,7);
        
    }
    ofFill();
    if (VUn4 >= -50){
        ofSetColor(104,244,66);
        ofDrawRectangle(VUx4,VUy - 20,20,7);
        
    }
    ofFill();
    if (VUn4 >= -35){
        ofSetColor(104,244,66);
        ofDrawRectangle(VUx4,VUy - 30,20,7);
        
    }
    ofFill();
    if (VUn4 >= -24){
        ofSetColor(200,244,66);
        ofDrawRectangle(VUx4,VUy - 40,20,7);
    }
    
    ofFill();
    if (VUn4 >= -18){
        ofSetColor(200,244,66);
        ofDrawRectangle(VUx4,VUy - 50,20,7);
        
    }
    ofFill();
    if (VUn4 >= -14){
        ofSetColor(244,241,66);
        ofDrawRectangle(VUx4,VUy - 60,20,7);
        
    }
    ofFill();
    if (VUn4 >= -12){
        ofSetColor(244,241,66);
        ofDrawRectangle(VUx4,VUy - 70,20,7);
        
    }
    ofFill();
    if (VUn4 >= -6){
        ofSetColor(244,191,66);
        ofDrawRectangle(VUx4,VUy - 80,20,7);
        
    }
    ofFill();
    if (VUn4 >= -3){
        ofSetColor(244,191,66);
        ofDrawRectangle(VUx4,VUy - 90,20,7);
        
    }
    
    ofFill();
    if (VUn4 >= 0){
        ofSetColor(244,66,66);
        ofDrawRectangle(VUx4,VUy - 100,20,15);
        
    }
    ofFill ();
    ofSetColor(200, 200, 200);
    ofDrawBitmapString("-24", VUx4 + 15, VUy - 30);
    ofDrawBitmapString("0", VUx4 + 15, VUy - 85);
    ofDrawBitmapString(amplint, VUx, VUy + 20);
    ofDrawBitmapString(amplint2, VUx2, VUy + 20);
    ofDrawBitmapString(amplint3, VUx3, VUy + 20);
    ofDrawBitmapString(amplint4, VUx4, VUy + 20);
        
        gui2.draw();
        gui3.draw();
        gui4.draw();
        audiosetup.draw();
        dspCpu.draw();
        
        
        
        
        if(audioset == true){ gui5.draw();
            
            
        
        ofDrawBitmapString(devicesstr, 250, 300);
        
        
        }
        if(instruct == true){
            
            string instructions =
            ofToString(
            "Instructions \n \n") +
            "Press 's' to save the parameters. \n"
            + "Press 'l' to load the parameters or click 'load initial parameters' to get ready. \n \n"
            + "Press '1' to start the piece. \n"
            + "Change the programs according to the score indication pressing respectivelly '2', '3', '4', and '5'. \n"
            + "Press '0' to play the final fadeout. \n"
            + "Press 'r' to reset all. \n  \n"
            + "Press 'h' to hide/show the menus. \n";
            
            ofDrawBitmapString(instructions, 250, 50);
            
            ofFill();
            ofSetColor(255, 255, 255);
            ofDrawCircle(15, h - 60, 10);
            ofDrawBitmapString("electroacoustic spatialization on P1 and P2", 30, h - 60);
            
            ofFill();
            ofSetColor(0);
            ofDrawCircle(15, h - 30, 10);
            ofSetColor(255);
            ofDrawBitmapString("flute spatialization on P3", 30, h - 30);
            
            
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::exit() {

	// cleanup
	sound.stop();

    applydev.removeListener(this, &ofApp::applydevButtonPressed);

    
    
}

//--------------------------------------------------------------
void ofApp::applydevButtonPressed(){
    
    pd.stop();
    sound.stop();
    
    
    gui5.saveToFile( "settingsgui5.xml" );

    exit();
    _Exit(1);
}

//--------------------------------------------------------------
void ofApp::loadallButtonPressed(){
    
    pd.stop();
    sound.stop();
    
    if(!pd.init(nOutputs, nInputs, 44100, ticksPerBuffer, false)) {
        OF_EXIT_APP(1);
    }
    pd.start();
    
    sound.setup(settings);
    
    
}
//--------------------------------------------------------------
void ofApp::difToggle(bool & pressed){
    
if(dif == true) {difstr = "stereo";}
else {difstr = "quadraphonic";}
    
}



//--------------------------------------------------------------
void ofApp::keyPressed (int key) {
    if( key == 'h' ){
        bHide = !bHide;
    }
    if(key == 's') {
        
        gui2.saveToFile("settings.xml");
        gui3.saveToFile("settings.xml");
        gui4.saveToFile("settings.xml");
        audiosetup.saveToFile( "settingsshows.xml" );

        

    }
    
    
    if(key == 'l') {
        gui2.loadFromFile("settings.xml");
        gui3.loadFromFile("settings.xml");
        gui4.loadFromFile("settings.xml");
        
        loadallButtonPressed();

        
    }
    if(key == ' '){
        color = ofColor(255);
    }
    if( key == '1' ){
        pd.sendFloat("programsFof", 1);
        progstring = "P1";
    }
    if( key == '2' ){
        pd.sendFloat("programsFof", 2);
        progstring = "P2";
    }
    if( key == '3' ){
        pd.sendFloat("programsFof", 3);
        progstring = "P3";
    }
    if( key == '4' ){
        pd.sendFloat("programsFof", 4);
        progstring = "P4";
    }
    if( key == '5' ){
        pd.sendFloat("programsFof", 5);
        progstring = "P5";
    }
    if( key == '0' ){
        pd.sendFloat("programsFof", 0);
        progstring = "the end";
    }
    if( key == 'r' ){
        pd.sendFloat("resetFof", 1);
        progstring = "reset";
    }
    
}

//--------------------------------------------------------------
void ofApp::audioReceived(float * input, int bufferSize, int nChannels) {
	pd.audioIn(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::audioRequested(float * output, int bufferSize, int nChannels) {
	pd.audioOut(output, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::print(const std::string& message) {
//	cout << message << endl;
}

//--------------------------------------------------------------
void ofApp::receiveBang(const std::string& dest) {
//	cout << "OF: bang " << dest << endl;
    
}

//--------------------------------------------------------------
void ofApp::receiveFloat(const std::string& dest, float value) {
    
    //Amplitude da flauta
    if (dest == "amplifluteFpd") {
        amplitude = value;
    }
    
    //Amplitude das 4 saidas
    if (dest == "ampliout1Fpd") {
        amplint = int (value);
    }
    if (dest == "ampliout2Fpd") {
        amplint2 = int (value);
    }
    if (dest == "ampliout3Fpd") {
        amplint2 = int (value);
    }
    if (dest == "ampliout4Fpd") {
        amplint2 = int (value);
    }
    
    //XY espacialização P1 e P2
    if (dest == "spatleavesXFpd") {
        lvspaX = value/100 * ofGetWidth();
    }
    if (dest == "spatleavesYFpd") {
        lvspaY = value/100 * ofGetHeight();
    }
    
    //XY espacialização P3
    if (dest == "spatfluteXFpd") {
        flspaX = value/100 * ofGetWidth();
    }
    if (dest == "spatfluteYFpd") {
        flspaY = value/100 * ofGetHeight();
    }
    if (dest == "cpuFpd") {
        fdspCpu = value * 10;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::receiveSymbol(const std::string& dest, const std::string& symbol) {
    
    if (dest == "programsFpd") {
        progstring = symbol;
        
        
    }
	//cout << "OF: symbol " << dest << ": " << symbol << endl;
}

//--------------------------------------------------------------
void ofApp::receiveList(const std::string& dest, const List& list) {
	//cout << "OF: list " << dest << ": ";

	// step through the list
	for(int i = 0; i < list.len(); ++i) {
		if(list.isFloat(i))
			cout << list.getFloat(i) << " ";
		else if(list.isSymbol(i))
			cout << list.getSymbol(i) << " ";
	}

	// you can also use the built in toString function or simply stream it out
	// cout << list.toString();
	// cout << list;

	// print an OSC-style type string
//	cout << list.types() << endl;
}

//--------------------------------------------------------------
void ofApp::receiveMessage(const std::string& dest, const std::string& msg, const List& list) {
	//cout << "OF: message " << dest << ": " << msg << " " << list.toString() << list.types() << endl;
}

//--------------------------------------------------------------
void ofApp::receiveNoteOn(const int channel, const int pitch, const int velocity) {
	//cout << "OF MIDI: note on: " << channel << " " << pitch << " " << velocity << endl;
}

//--------------------------------------------------------------
void ofApp::receiveControlChange(const int channel, const int controller, const int value) {
	//cout << "OF MIDI: control change: " << channel << " " << controller << " " << value << endl;
}

// note: pgm nums are 1-128 to match pd
void ofApp::receiveProgramChange(const int channel, const int value) {
//	cout << "OF MIDI: program change: " << channel << " " << value << endl;
}

//--------------------------------------------------------------
void ofApp::receivePitchBend(const int channel, const int value) {
	//cout << "OF MIDI: pitch bend: " << channel << " " << value << endl;
}

//--------------------------------------------------------------
void ofApp::receiveAftertouch(const int channel, const int value) {
	//cout << "OF MIDI: aftertouch: " << channel << " " << value << endl;
}

//--------------------------------------------------------------
void ofApp::receivePolyAftertouch(const int channel, const int pitch, const int value) {
	//cout << "OF MIDI: poly aftertouch: " << channel << " " << pitch << " " << value << endl;
}

// note: pd adds +2 to the port num, so sending to port 3 in pd to [midiout],
//       shows up at port 1 in ofxPd

void ofApp::receiveMidiByte(const int port, const int byte) {
	//cout << "OF MIDI: midi byte: " << port << " " << byte << endl;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    //screenSize = ofToString(w) + "x" + ofToString(h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

