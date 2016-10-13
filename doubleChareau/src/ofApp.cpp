#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(30);

    frontMovie.load("movies/newFront.mp4");
    frontMovie.play();
    //clippingPlaneMovie.setPaused(true);

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

    int currentFrame = frontMovie.getCurrentFrame();
    /*
    if (currentFrame == frameNumber) {
        clippingPlaneMovie.setPaused(true);
    } else if (currentFrame < frameNumber) {
        clippingPlaneMovie.nextFrame();
    } else if (currentFrame > frameNumber) {
        clippingPlaneMovie.previousFrame();
    }*/

    frontMovie.update();
    rearMovie.update();

    for(int i = 0; i < server.getLastID(); i++) // getLastID is UID of all clients
    {
        //cout << "CONNECTED: " << server.isClientConnected(i) << "\n";
        if( server.isClientConnected(i) ) { // check and see if it's still around
            // maybe the client is sending something
            server.receiveRawBytes(i, recv, 63);
            cout << "RECIEVED MODBUS: " << '\n';
            cout << "Transaction ID: " << (unsigned int)recv[0] << " " << (unsigned int)recv[1] << '\n';
            cout << "Protocol ID: " << (unsigned int)recv[2] << " " << (unsigned int)recv[3] << '\n';
            cout << "Length: " << (int)recv[4] << " " << (int)recv[5] << '\n';
            cout << "Unit ID: " << (int)recv[6] << '\n';
            cout << "Function Code: " << (int)recv[7] << '\n';
            cout << "Data: ";

            for (int c = 8; c <= (int)recv[5] + 8; c++) {
                cout << (unsigned int)recv[c] << " ";
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
