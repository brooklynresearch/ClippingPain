#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){

  ofGLFWWindowSettings settings;
  settings.width = 768;
  settings.height = 1024;
  settings.setPosition(ofVec2f(0,0));
  shared_ptr<ofAppBaseWindow> leftWindow = ofCreateWindow(settings);

  settings.width = 768;
  settings.height = 1024;
  settings.setPosition(ofVec2f(768,0));
  settings.shareContextWith = leftWindow;
  shared_ptr<ofAppBaseWindow> rightWindow = ofCreateWindow(settings);

  shared_ptr<ofApp> mainApp(new ofApp);

  mainApp->setupRight();
  ofAddListener(rightWindow->events().draw, mainApp.get(), &ofApp::drawRight);

	ofRunApp(leftWindow, mainApp);
  ofRunMainLoop();
}
