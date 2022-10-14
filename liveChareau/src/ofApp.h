#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void setupRight();
		void update();
		void draw();
		void drawRight(ofEventArgs &args);

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
    
    int PORT;
    ofxOscReceiver receiver;

    string indexLeft = "0";
    string currentLeft;
    string filenameLeft;
    ofVideoPlayer vplayerLeft;
    string indexRight = "2";
    string currentRight;
    string filenameRight;
    ofVideoPlayer vplayerRight;
    
    // 0 draws on the wall with closet and elevator
    // 1 on opposite
    vector<int> alternator {1,1,0,1,0,0,1,1,1,0,0};
};
