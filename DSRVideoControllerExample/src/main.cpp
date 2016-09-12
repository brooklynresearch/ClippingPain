#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(1900,1424, OF_WINDOW);			// <-------- setup the GL context
    
//    ofGLFWWindowSettings settings;
//    settings.multiMonitorFullScreen = true;
//    settings.windowMode = OF_WINDOW;
//    ofCreateWindow(settings);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
