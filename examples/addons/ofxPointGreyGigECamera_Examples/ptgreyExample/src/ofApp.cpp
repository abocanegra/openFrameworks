#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel( OF_LOG_VERBOSE );

    ofSetVerticalSync(true);

    //vidGrabber.listDevices();
	//vidGrabber.setDeviceID(0);

	grayImage.allocate(640,480);

}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(100,100,100);




}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetHexColor(0xffffff);
    //vidGrabber.draw( 100,100 );
	grayImage.draw(200,100);

	ofSetHexColor(0xffffff);
	char reportStr[1024];
	sprintf(reportStr, "fps: %f", ofGetFrameRate());
	ofDrawBitmapString(reportStr, 20, 600);

}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){

	switch (key){
		case ' ':
			break;
	}
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
void ofApp::mouseReleased(){

}
