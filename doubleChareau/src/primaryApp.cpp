#include "primaryApp.h"

//--------------------------------------------------------------
void primaryApp::setup(){
    
    ofSetFrameRate(30);
    
    clippingPlaneMovie.load("movies/movie1.mov");
    clippingPlaneMovie.play();
    clippingPlaneMovie.setPaused(true);
    
    server.setup(5020);

}

//--------------------------------------------------------------
void primaryApp::update(){
    
    int currentFrame = clippingPlaneMovie.getCurrentFrame();
    
    if (currentFrame == frameNumber) {
        clippingPlaneMovie.setPaused(true);
    } else if (currentFrame < frameNumber) {
        clippingPlaneMovie.nextFrame();
    } else if (currentFrame > frameNumber) {
        clippingPlaneMovie.previousFrame();
    }
    
    clippingPlaneMovie.update();
    
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
            
            frameNumber = (int)value;

            server.sendRawMsg(i, recv, (int)recv[5] + 8);
            
        }
    }
}

//--------------------------------------------------------------
void primaryApp::draw(){

    clippingPlaneMovie.draw(0,0, 950, 712);

}

//--------------------------------------------------------------
void primaryApp::keyPressed(int key){

}

//--------------------------------------------------------------
void primaryApp::keyReleased(int key){

}

//--------------------------------------------------------------
void primaryApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void primaryApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void primaryApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void primaryApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void primaryApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void primaryApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void primaryApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void primaryApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void primaryApp::dragEvent(ofDragInfo dragInfo){ 

}
