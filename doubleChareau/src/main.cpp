#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
/*
    ofGLFWWindowSettings settings;
    settings.width = 950;
    settings.height = 712;
    settings.setPosition(ofVec2f(0,0));
    shared_ptr<ofAppBaseWindow> frontWindow = ofCreateWindow(settings);

    settings.width = 950;
    settings.height = 712;
    settings.setPosition(ofVec2f(2000,0));
    settings.shareContextWith = frontWindow;
    shared_ptr<ofAppBaseWindow> rearWindow = ofCreateWindow(settings);

    shared_ptr<ofApp> mainApp(new ofApp);

    mainApp->setupRear();
    ofAddListener(rearWindow->events().draw, mainApp.get(), &ofApp::drawRear);

    ofRunApp(frontWindow, mainApp);
    ofRunMainLoop();
*/

  ofAppGLFWWindow window;
  window.setMultiDisplayFullscreen(true);
  ofSetupOpenGL(&window, 1920, 1080, OF_FULLSCREEN);
  ofRunApp(new ofApp());
}

