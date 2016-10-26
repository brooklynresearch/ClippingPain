#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
  ofAppGLFWWindow window;
  window.setMultiDisplayFullscreen(true);
  ofSetupOpenGL(&window, 1920, 1080, OF_FULLSCREEN);
  ofRunApp(new ofApp());
}

