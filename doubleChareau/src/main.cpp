#include "ofMain.h"
#include "primaryApp.h"
#include "secondaryApp.h"


//========================================================================
int main( ){
    ofGLWindowSettings settings;
    settings.width = 950;
    settings.height = 712;
    settings.setPosition(ofVec2f(0,0));
    auto mainWindow = ofCreateWindow(settings);
    
    settings.width = 950;
    settings.height = 712;
    settings.setPosition(ofVec2f(2000,0));
    auto secondWindow = ofCreateWindow(settings);
    
    auto mainApp = make_shared<primaryApp>();
    auto secondApp = make_shared<secondaryApp>();
    
    ofRunApp(secondWindow, secondApp);
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
