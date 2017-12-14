#pragma once

#include "ofMain.h"
#include "PGRCamera.h"

class ofApp : public ofBaseApp
{
	public:
		void setup();
		void update();
		void draw();
        bool initDelay();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        unsigned int loader;
        bool         initialized;
		//PGR CAMERA
        FlyCapture2::PGRCamera listCam;
        FlyCapture2::PGRCamera cams[4];


    protected:
    private:
        uint64_t    totalNumCameras;
        bool        camerasAvailable;
        bool        checkAvailableCameras();

};
