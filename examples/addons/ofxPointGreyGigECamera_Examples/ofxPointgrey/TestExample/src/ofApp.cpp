#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camWidth    = 640;
    camHeight   = 480;

	if( !vidGrabber.initGrabber(camWidth, camHeight, (unsigned int)CAMERA) ){//cameraSerialNr
		ofLog(OF_LOG_FATAL_ERROR, "sorry, no camera found - exit application!");
		ofExit();
	}

    curFrame.allocate(camWidth, camHeight, OF_IMAGE_GRAYSCALE);
}

//--------------------------------------------------------------
void ofApp::update(){
    bool bNewFrame = false;
    vidGrabber.grabFrame();
	bNewFrame = vidGrabber.isFrameNew();
    if( bNewFrame ) {
        curFrame.setFromPixels(vidGrabber.getPixels(), camWidth, camHeight, OF_IMAGE_GRAYSCALE);
        curFrame.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
	curFrame.draw(0, 0); //draw your grabbed image
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
