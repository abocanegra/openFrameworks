#include "ofApp.h"

//--------------------------------------------------------------

int main( ){
//    ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
    ofGLWindowSettings settings;
    settings.setGLVersion(3, 2);  // Programmable pipeline
    settings.width = 1024;
    settings.height = 768;
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}
