#pragma once

#include "ofMain.h"
#include "ofxTCPServer.h"

class ofApp : public ofBaseApp{

  public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofXml XML;

    ofVideoPlayer frontMovie;

    string frontFile;
    string rearFile;

    int movieWidth;
    int movieHeight;

    ofxTCPServer server;
    char recv[64];

    int frameRate;
    float numFrames;
    int targetFrame = 0;
    int currentFrame = 0;
    int prevTarget = 0;

    int totalCues = 34;
    int prevCue = 0;
    
    int MSG_LENGTH = 16;

    vector<int> timeIntervals;
    map<int, int> cues;

    int currentTime;
    int currentInterval = 0;
    int frameTicker = 0;

    bool debug;
};

