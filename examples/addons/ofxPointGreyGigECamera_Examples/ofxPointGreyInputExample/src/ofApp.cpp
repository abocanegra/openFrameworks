#include "ofApp.h"

void ofApp::exit(){

	delete cam;
}

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0,0,0);
	ofEnableAlphaBlending();
	ofEnableSmoothing();
	ofSetFrameRate(60);
	ofSetVerticalSync(true);

	cam = new CameraInput(1920, 1200,
							 VID_FORMAT_RGB,
							 45,
							 true,		//discard frames
							 false,		//use texture
							 false		//mode7	(needed to get 320 x 240 from the firefly MV)
							 );

}

//--------------------------------------------------------------
void ofApp::update(){
	cam->update();

}

//--------------------------------------------------------------
void ofApp::draw(){
ofSetHexColor(0xffffff);
	if ( cam->getWarpedCamImage() != NULL )
		cam->getWarpedCamImage()->draw(0, 0, ofGetWidth(), ofGetHeight());
	cam->draw();	//UI and suff
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
