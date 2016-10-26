#include "ofApp.h"
#include <cstring>

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
//    ofSetFrameRate(30);

    if (XML.load("settings.xml") ){
      XML.setTo("moviefiles");
      ofLog() << "XML loaded" << endl;
    }

    frontFile = XML.getValue("moviefile[@id=front]/filename");
    rearFile = XML.getValue("moviefile[@id=rear]/filename");

    movieWidth = stoi(XML.getValue("dimensions/width"));
    movieHeight = stoi(XML.getValue("dimensions/height"));

    frontMovie.load("movies/" + frontFile);
    frontMovie.play();
    frontMovie.setPaused(true);

    rearMovie.load("movies/" + rearFile);
    rearMovie.play();
    rearMovie.setPaused(true);

    numFrames = frontMovie.getTotalNumFrames();
    cout << "Video Frames: " << numFrames << "\n\n";

    server.setup(5020);
    server.setVerbose(true);

}

//--------------------------------------------------------------
/*
void ofApp::setupRear(){

    rearMovie.load("movies/newRear.mp4");
    rearMovie.play();

}
*/
//--------------------------------------------------------------
void ofApp::update(){

    //frameNumber++;

    frontMovie.update();
    rearMovie.update();

    currentFrame = frontMovie.getCurrentFrame();
    //cout << endl << "Frame: " << currentFrame << endl;
/*
    */
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

            uint32_t value = (uint8_t)recv[13];
            value <<= 8;
            value += (uint8_t)recv[14];
            value <<= 8;
            value += (uint8_t)recv[15];
            value <<= 8;
            value += (uint8_t)recv[16];

            cout << '\n';
            cout << "BYTE VALUE: " << value << '\n';
            float floatValue;
            value = (float)value;
            floatValue = *((float*)&value);
            cout << "FLOAT VALUE: " << floatValue << '\n';
            cout << '\n';

            float ratio = ofMap(floatValue, 0, 1000, 0, numFrames);

            pos = ofMap(floatValue, 0, 1060, 0, 1);
            cout << "Position: " << pos << "%" << "\n\n";

            frameNumber = (int)ratio;

            //char res[] = {0,1,0,0,0,6,0,16,0,0,0,10};

            //server.sendRawBytes(i, res, 12);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    if (currentFrame == frameNumber) {
          frontMovie.setPaused(true);
      } else if (currentFrame < frameNumber) {
          frontMovie.nextFrame();
      } else if (currentFrame > frameNumber) {
          frontMovie.previousFrame();
      }

    //frontMovie.setPosition(pos);
    frontMovie.draw(0,0, movieWidth, movieHeight);
    rearMovie.draw(1920, 0, movieWidth, movieHeight);
    string frame = ofToString(currentFrame);
    ofDrawBitmapString("Frame Number: " + frame, 50, 50);

}
/*
//--------------------------------------------------------------
void ofApp::drawRear(ofEventArgs &args){

    rearMovie.draw(0,0, 950, 712);
}
*/
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

