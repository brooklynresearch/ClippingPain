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
    ofVideoPlayer rearMovie;

    string frontFile;
    string rearFile;

    int movieWidth;
    int movieHeight;

    ofxTCPServer server;
    char recv[64];

    float numFrames;
    int frameNumber = 0;

    int currentFrame = 0;

    int MSG_LENGTH = 33;

    float pos;
};

