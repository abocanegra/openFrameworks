#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //Base Setup
    ofBackground(20,20,20);
	ofSetWindowTitle("ofxPointGreyGigE Example");
    ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.

    loader =  ofGetElapsedTimeMillis();

    //List Devices and Instantiate Devices
    totalNumCameras = 0;
    camerasAvailable = checkAvailableCameras();
}

//--------------------------------------------------------------
void ofApp::update()
{
    if(camerasAvailable){
        for(uint64_t i=0; i<totalNumCameras;i++){
            cams[i].update();
        }
    }else{
        listCam.listUpdate();
        camerasAvailable = checkAvailableCameras();
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    //Delay initialization To allow everything to get up to speed
    if(!initialized){
        initialized = initDelay();
    }

    //Check initialized and cameras available then draw image
    if(!camerasAvailable && initialized){
        listCam.listDraw(); //Print to screen the loading message.
    }else{
        for(uint64_t i=0; i<totalNumCameras;i++){
            cams[i].draw();
        }
    }
}

//--------------------------------------------------------------
bool ofApp::checkAvailableCameras(){
    totalNumCameras = listCam.listDevices();
    if(totalNumCameras > 0 && !camerasAvailable){
        for(uint64_t i=0; i<totalNumCameras;i++){
            //instantiate cameras to PGRCamera cam[4] array
            ofLog(OF_LOG_NOTICE,"Insantiating Camera %i\n", i);
            //"MONO" || "RGB" - default
            cams[i].setup(i);
      }
        return true;
    }
    return false;
}

//--------------------------------------------------------------
bool ofApp::initDelay(){
    loader =  ofGetElapsedTimeMillis();
    if(loader < 3000){
        ofSetHexColor(0xffffff);
        string loadChar= ".";
        if(loader <= 1000){
            loadChar += ".";
        }else if(loader <= 2000){
            loadChar += "..";
        }else if(loader <= 3000){
            loadChar +="...";
        }
        ofDrawBitmapString("Initializing" + loadChar,100, 100);
        return false;
   }
   return true;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
