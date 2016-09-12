#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255,255,255);
    ofSetVerticalSync(true);
    frameByframe = false;
    
    // Uncomment this to show movies with alpha channels
    // fingerMovie.setPixelFormat(OF_PIXELS_RGBA);
    
    clippingPlaneMovie.load("movies/16_0819_Clipping Plane_76SecEachWay.mp4");
    clippingPlaneMovie.setLoopState(OF_LOOP_NORMAL);
    clippingPlaneMovie.play();
    
    //
    cout << "Position: " << clippingPlaneMovie.getPosition() << "\n";
    
    // listen on the given port
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
    
    current_msg_string = 0;
    mouseX = 0;
    mouseY = 0;
    mouseButtonState = "";
    sliderTotal = 1022;
}

//--------------------------------------------------------------
void ofApp::update(){
    clippingPlaneMovie.update();
    // hide old messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msg_strings[i] = "";
        }
    }
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // check for mouse moved message
        if(m.getAddress() == "/slider"){
            // both the arguments are int32's
            frameNumber = m.getArgAsInt32(0);
            //frameNumber =  ((float)mouseX/(float)sliderTotal) * clippingPlaneMovie.getTotalNumFrames();
            //cout << "FRAME: " << frameNumber << "\n";
        }
        // check for mouse button message
        else if(m.getAddress() == "/button/0"){
            // the single argument is a string
            mouseButtonState = m.getArgAsString(0);
            mouseButtonState = "BUTTON ZERO";
            clippingPlaneMovie.firstFrame();
        }
        else if(m.getAddress() == "/button/1"){
            // the single argument is a string
            buttonOneState = m.getArgAsString(0);
            mouseButtonState = "BUTTON ONE";
            clippingPlaneMovie.firstFrame();
        }
        else if(m.getAddress() == "/button/2"){
            // the single argument is a string
            buttonTwoState = m.getArgAsString(0);
            mouseButtonState = "BUTTON TWO";
            clippingPlaneMovie.firstFrame();
        }
        // check for an image being sent (note: the size of the image depends greatly on your network buffer sizes - if an image is too big the message won't come through )
        else if(m.getAddress() == "/image" ){
            ofBuffer buffer = m.getArgAsBlob(0);
            receivedImage.load(buffer);
        }
        
        else{
            /*
            // unrecognized message: display on the bottom of the screen
            string msg_string;
            msg_string = m.getAddress();
            msg_string += ": ";
            for(int i = 0; i < m.getNumArgs(); i++){
                // get the argument type
                msg_string += m.getArgTypeName(i);
                msg_string += ":";
                // display the argument - make sure we get the right type
                if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                    msg_string += ofToString(m.getArgAsInt32(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    msg_string += ofToString(m.getArgAsFloat(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                    msg_string += m.getArgAsString(i);
                }
                else{
                    msg_string += "unknown";
                }
            }
            // add to the list of strings to display
            msg_strings[current_msg_string] = msg_string;
            timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
            current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
            // clear the next line
            msg_strings[current_msg_string] = "";
             */
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetHexColor(0xFFFFFF);
    
    clippingPlaneMovie.setFrame(frameNumber);
    clippingPlaneMovie.draw(0,0);
    ofSetHexColor(0x000000);
    /*
    ofPixels & pixels = clippingPlaneMovie.getPixels();
    
    int vidWidth = pixels.getWidth();
    int vidHeight = pixels.getHeight();
    int nChannels = pixels.getNumChannels();
    
    // let's move through the "RGB(A)" char array
    // using the red pixel to control the size of a circle.
    for (int i = 4; i < vidWidth; i+=8){
        for (int j = 4; j < vidHeight; j+=8){
            unsigned char r = pixels[(j * 320 + i)*nChannels];
            float val = 1 - ((float)r / 255.0f);
            ofDrawCircle(400 + i,20+j,10*val);
        }
    }
    

    ofSetHexColor(0x000000);
    ofDrawBitmapString("press f to change",20,320);
    if(frameByframe) ofSetHexColor(0xCCCCCC);
    ofDrawBitmapString("mouse speed position",20,340);
    if(!frameByframe) ofSetHexColor(0xCCCCCC); else ofSetHexColor(0x000000);
    ofDrawBitmapString("keys <- -> frame by frame " ,190,340);
    ofSetHexColor(0x000000);
    
    ofDrawBitmapString("frame: " + ofToString(clippingPlaneMovie.getCurrentFrame()) + "/"+ofToString(clippingPlaneMovie.getTotalNumFrames()),20,380);
    ofDrawBitmapString("duration: " + ofToString(clippingPlaneMovie.getPosition()*clippingPlaneMovie.getDuration(),2) + "/"+ofToString(clippingPlaneMovie.getDuration(),2),20,400);
    ofDrawBitmapString("speed: " + ofToString(clippingPlaneMovie.getSpeed(),2),20,420);
    
    if(clippingPlaneMovie.getIsMovieDone()){
        ofSetHexColor(0xFF0000);
        ofDrawBitmapString("end of movie",20,440);
    }
    
    string buf;
    buf = "listening for osc messages on port" + ofToString(PORT);
    ofDrawBitmapString(buf, 20, 500);
    
    if(receivedImage.getWidth() > 0){
        ofDrawBitmapString("Image:", 20, 660);
        receivedImage.draw(10, 780);
    }
    
    // draw mouse state
    buf = "mouse: " + ofToString(mouseX, 4) +  " " + ofToString(mouseY, 4);
    ofDrawBitmapString(buf, 430, 500);
    ofDrawBitmapString(mouseButtonState, 580, 500);
    
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        ofDrawBitmapString(msg_strings[i], 20, 520 + 15 * i);
    }
    */
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    switch(key){
        case 'f':
            frameByframe=!frameByframe;
            clippingPlaneMovie.setPaused(frameByframe);
            break;
        case OF_KEY_LEFT:
            clippingPlaneMovie.previousFrame();
            break;
        case OF_KEY_RIGHT:
            clippingPlaneMovie.nextFrame();
            break;
        case '0':
            clippingPlaneMovie.firstFrame();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    /*
    if(!frameByframe){
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        float speed = (2 * pct - 1) * 5.0f;
        clippingPlaneMovie.setSpeed(speed);
    }
    */
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    /*
    if(!frameByframe){
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        clippingPlaneMovie.setPosition(pct);
    }
    */
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(!frameByframe){
        clippingPlaneMovie.setPaused(true);
    }
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(!frameByframe){
        clippingPlaneMovie.setPaused(false);
    }
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