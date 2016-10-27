#include "ofApp.h"
#include <cstring>

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofSetFrameRate(30);

    if (XML.load("settings.xml") ){
      XML.setTo("moviefiles");
      ofLog() << "XML loaded" << endl;
    }

    frontFile = XML.getValue("moviefile[@id=front]/filename");
    rearFile = XML.getValue("moviefile[@id=rear]/filename");

    movieWidth = stoi(XML.getValue("dimensions/width"));
    movieHeight = stoi(XML.getValue("dimensions/height"));

    XML.setToSibling();
    for (int i = 1; i < 34; i++) {
      int cueNum = i;
      int targetFrame = stoi(XML.getValue("cue[@id="+to_string(i)+"]/framenumber"));
      cues.emplace(cueNum, targetFrame);
    }

    for(auto& item : cues) {
      cout << "cue " << item.first << ": " << item.second << endl;
    }

    frontMovie.load("movies/" + frontFile);
    frontMovie.play();
    //frontMovie.setPaused(true);

//    rearMovie.load("movies/" + rearFile);
//    rearMovie.play();
    //rearMovie.setPaused(true);

    numFrames = frontMovie.getTotalNumFrames();
    cout << "Video Frames: " << numFrames << "\n\n";

    server.setup(5020);
    server.setVerbose(true);

}

//--------------------------------------------------------------
void ofApp::update(){

    //frameNumber++;

    frontMovie.update();
 //   rearMovie.update();

    currentFrame = frontMovie.getCurrentFrame();

    //cout << endl << "Frame: " << currentFrame << endl;

    for(int i = 0; i < server.getLastID(); i++) // getLastID is UID of all clients
    {
        if( server.isClientConnected(i) ) { // check and see if it's still around
            // maybe the client is sending something
            server.receiveRawBytes(i, recv, 63);
            cout << "RECIEVED MODBUS: " << '\n';
            cout << "Transaction ID: " << (int)recv[0] << " " << (int)recv[1] << '\n';
            cout << "Protocol ID: " << (int)recv[2] << " " << (int)recv[3] << '\n';
            cout << "Length: " << (int)recv[4] << " " << (int)recv[5] << '\n';
            cout << "Unit ID: " << (int)recv[6] << '\n';
            cout << "Function Code: " << (int)recv[7] << '\n';
            cout << "Data: ";

            for (int c = 8; c < MSG_LENGTH; c++) {
                cout << (int)recv[c] << " ";
            }

            uint32_t cueNum = (uint8_t)recv[13];
            cueNum <<= 8;
            cueNum += (uint8_t)recv[14];
            cueNum <<= 8;
            cueNum += (uint8_t)recv[15];
            cueNum <<= 8;
            cueNum += (uint8_t)recv[16];

            cout << '\n';
            cout << "BYTE VALUE: " << hex << cueNum << '\n';
            //float floatValue;
            //value = (float)value;
            //floatValue = *((float*)&value);
            cout << "CUE VALUE: " << cueNum << '\n';
            cout << '\n';

            //float ratio = ofMap(floatValue, 0, 1060, 0, numFrames);

            //pos = ofMap(floatValue, 0, 1060, 0, 1);
            //cout << "Position: " << pos << "%" << "\n\n";

            int cue = cues.find(cueNum)->second;
            if (cue == 0) {
              targetFrame++;
            } else if (cue > 0) {
              targetFrame = cue;
            }
            cout << "Target Frame: " << targetFrame << "\n\n";

            //char res[] = {0,1,0,0,0,6,0,16,0,0,0,10};

            //server.sendRawBytes(i, res, 12);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    if (currentFrame == targetFrame) {
        frontMovie.setPaused(true);
    } else if (currentFrame < targetFrame) {
        frontMovie.nextFrame();
    } else if (currentFrame > targetFrame) {
        frontMovie.previousFrame();
    }

    
    //frontMovie.setPosition(pos);
    frontMovie.draw(0,0, movieWidth, movieHeight);
  //  rearMovie.draw(movieWidth, 0, movieWidth, movieHeight);
    string frame = ofToString(currentFrame);
    ofDrawBitmapString("Frame: " + frame, 50, 50);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

