#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxVideoGrabberPtgrey.h"



class ofApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased();

    ofxVideoGrabberPtgrey    vidGrabber;
	ofxCvGrayscaleImage 	grayImage;

};
