#include "ofApp.h"
#include <cstring>

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);

    if (XML.load("settings.xml") ){
      XML.setTo("moviefiles");
      ofLog() << "XML loaded" << endl;
    }

    PORT = 12345;
    HOST = "192.168.3.209";
    sender.setup(HOST, PORT);
    
    frameRate = stoi(XML.getValue("framerate"));
    ofSetFrameRate(frameRate);

    ofHideCursor();
    
    frontFile = XML.getValue("moviefile[@id=front]/filename");
    rearFile = XML.getValue("moviefile[@id=rear]/filename");

    movieWidth = stoi(XML.getValue("dimensions/width"));
    movieHeight = stoi(XML.getValue("dimensions/height"));

    XML.setToSibling();
    for (int i = 0; i < 34; i++) {
      int cueNum = i;
      int targetFrame = stoi(XML.getValue("cue[@id="+to_string(i)+"]/framenumber"));
      timeIntervals.push_back(stof(XML.getValue("cue[@id="+to_string(i)+"]/interval")) * 1000);
      cues.emplace(cueNum, targetFrame);
    }

    cout << "CUES" << endl;
    for(auto& item : cues) {
      cout << "cue " << item.first << ": " << item.second << endl;
    }
    cout << endl;

    cout << "TIME INTERVALS" << endl;
    for(auto& interval : timeIntervals) {
      cout << to_string(interval) << endl;
    }

    frontMovie.load("movies/" + frontFile);
    frontMovie.play();
    frontMovie.setPaused(true);
    frontMovie.setFrame(2);

    numFrames = frontMovie.getTotalNumFrames();
    cout << "Video Frames: " << numFrames << "\n\n";

    server.setup(5020);
    server.setVerbose(true);

}

//--------------------------------------------------------------
void ofApp::update(){

    frontMovie.update();

    currentFrame = frontMovie.getCurrentFrame();
    currentTime = ofGetElapsedTimeMillis();

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
            cout << "BYTE VALUE: " << (int)cueNum << '\n';
            float floatValue;
            cueNum = (float)cueNum;
            floatValue = *((float*)&cueNum);
            cout << "CUE VALUE: " << cueNum << '\n';
            cout << '\n';

//            if(prevCue == 33 && cueNum == 1){
//                frontMovie.setFrame(0);
//            }
//            
//            if(prevCue != cueNum)
//            {
//                
//                prevCue = cueNum;
//                prevTarget = targetFrame;
//                
//                ofxOscMessage m;
//                m.setAddress("/vid");
//                m.addIntArg(triggerVids[cueNum]);
//                
//                sender.sendMessage(m);
//            }
            // Ezer's test
            char recvByte[sizeof(float)];

            recvByte[0] = recv[16];
            recvByte[1] = recv[15];
            recvByte[2] = recv[14];
            recvByte[3] = recv[13];
            
            memcpy(&floatValue, recvByte, sizeof floatValue);
            
            cueNum = (int)floatValue;
            
            cout << "Ezer's float value " << floatValue << endl;

            
            
            if(prevCue != cueNum)
            {
                if(prevCue == 33 && cueNum == 1){
                    frontMovie.setFrame(0);
                }
                
                prevCue = cueNum;
                prevTarget = targetFrame;
                
                ofxOscMessage m;
                m.setAddress("/vid");
                m.addIntArg(triggerVids[cueNum]);
                
                sender.sendMessage(m);
            }
            
            if (cueNum != 0) {
                int cue = cues.find(cueNum)->second;
                if (cue > 0) {
//                    prevTarget = targetFrame;
                    targetFrame = cue;
                    currentInterval = timeIntervals[cue];
                    if(targetFrame - prevTarget > 0)
                    {
                        frameTicker = currentInterval / (targetFrame - prevTarget);
                    }
                }
            }
            cout << "Target Frame: " << targetFrame << "\n\n";

        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    if (currentTime >= frameTicker && currentFrame < targetFrame) {
        frontMovie.nextFrame();
        ofResetElapsedTimeCounter();
    }

  /*
    if (currentFrame == targetFrame) {
        frontMovie.setPaused(true);
    } else if (currentFrame < targetFrame) {
        frontMovie.nextFrame();
    } else if (currentFrame > targetFrame) {
        frontMovie.previousFrame();
    }*/

    
    //frontMovie.setPosition(pos);
    frontMovie.draw(0,0, movieWidth, movieHeight);
    string frame = ofToString(currentFrame);
    ofDrawBitmapString("Frame: " + frame, 50, 50);
    ofDrawBitmapString("Target: " + to_string(targetFrame), 50, 75);
    ofDrawBitmapString("Previous Target: " + to_string(prevTarget), 50, 100);
    ofDrawBitmapString("FrameRate: " + to_string(frameRate), 50, 150);
    ofDrawBitmapString("Interval: " + to_string(currentInterval), 50, 200);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r'){
        frontMovie.setFrame(targetFrame);
    }
    
    else if(key == '-' || key == '_'){
        --frameRate;
        ofSetFrameRate(frameRate);
    }
    
    else if(key == '=' || key == '+')
    {
        ++frameRate;
        ofSetFrameRate(frameRate);
    }
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

