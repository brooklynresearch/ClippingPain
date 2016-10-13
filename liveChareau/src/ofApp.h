#pragma once

#include "ofMain.h"

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

    string indexLeft = "1";
    string currentLeft;
    string filenameLeft;
    ofVideoPlayer vplayerLeft;

    string indexRight = "2";
    string currentRight;
    string filenameRight;
    ofVideoPlayer vplayerRight;
};
