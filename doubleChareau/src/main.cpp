#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
  ofAppGLFWWindow window;
  window.setMultiDisplayFullscreen(true);
  ofSetupOpenGL(&window, 1344, 1008, OF_FULLSCREEN);
  ofRunApp(new ofApp());
}

