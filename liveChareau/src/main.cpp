#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){

    ofAppGLFWWindow window;
    window.setMultiDisplayFullscreen(true);
    ofSetupOpenGL(&window, 1920, 1080, OF_FULLSCREEN);
    ofRunApp(new ofApp());
    /*
  ofGLFWWindowSettings settings;
  settings.width = 1920*2;
  settings.height = 1080;
  settings.setPosition(ofVec2f(0,0));
  shared_ptr<ofAppBaseWindow> leftWindow = ofCreateWindow(settings);

  settings.width = 768;
  settings.height = 1024;
  settings.setPosition(ofVec2f(768,0));
  settings.shareContextWith = leftWindow;
  //shared_ptr<ofAppBaseWindow> rightWindow = ofCreateWindow(settings);

  shared_ptr<ofApp> mainApp(new ofApp);

  mainApp->setupRight();
  //ofAddListener(rightWindow->events().draw, mainApp.get(), &ofApp::drawRight);

	ofRunApp(leftWindow, mainApp);
  ofRunMainLoop();
     */
}
