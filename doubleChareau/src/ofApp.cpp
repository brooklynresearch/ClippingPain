#include "ofApp.h"
#include <cstring>

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(30);

    frontMovie.load("movies/newFront.mp4");
    frontMovie.play();
    frontMovie.setPaused(true);

    numFrames = frontMovie.getTotalNumFrames();

    server.setup(5020);
    server.setVerbose(true);

}

//--------------------------------------------------------------
void ofApp::setupRear(){

    rearMovie.load("movies/newRear.mp4");
    rearMovie.play();

}

//--------------------------------------------------------------
void ofApp::update(){

    frontMovie.update();
    rearMovie.update();

    int currentFrame = frontMovie.getCurrentFrame();

    if (currentFrame == frameNumber) {
        frontMovie.setPaused(true);
    } else if (currentFrame < frameNumber) {
        frontMovie.nextFrame();
    } else if (currentFrame > frameNumber) {
        frontMovie.previousFrame();
    }

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

            float ratio = ofMap(floatValue, 0, 1000, 0, numFrames);

            frameNumber = (int)ratio;

            char res[] = {0,1,0,0,0,6,0,16,0,0,0,10};

            server.sendRawBytes(i, res, 12);

            memset(recv, 0, 64);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    frontMovie.draw(0,0, 950, 712);

}

//--------------------------------------------------------------
void ofApp::drawRear(ofEventArgs &args){

    rearMovie.draw(0,0, 950, 712);
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

