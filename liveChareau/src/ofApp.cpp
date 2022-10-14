#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    PORT = 12345;
    receiver.setup(PORT);
    
    ofSetFullscreen(true);
    ofHideCursor();
    
    CGDisplayHideCursor(NULL);
    
    ofSetBackgroundColor(0, 0, 0);
    if (XML.load("settings.xml") ){
        XML.setTo("films");
        ofLog() << "XML loaded" << endl;
    }
    currentLeft = "0";
  //filenameLeft = XML.getValue("film[@id=1]/filename");
  //ofLog() << "filename left: " << filenameLeft << endl;
  vplayerLeft.setLoopState(OF_LOOP_NONE);
  //vplayerLeft.load("films/" + filenameLeft);
    //vplayerLeft.setLoopState(OF_LOOP_NONE);
  //vplayerLeft.play();
    
    
    ofLog() << "starting" << endl;
}


//--------------------------------------------------------------
/*
void ofApp::setupRight(){

    ofHideCursor();
  if (XML.load("settings.xml") ){
    XML.setTo("films");
    ofLog() << "XML loaded" << endl;
  }
    ofSetBackgroundColor(0,0,0);
  currentRight = "2";
  filenameRight = XML.getValue("film[@id=2]/filename");
  ofLog() << "filename right: " << filenameRight << endl;
  vplayerRight.setLoopState(OF_LOOP_NONE);
  vplayerRight.load("films/" + filenameRight);
  //vplayerRight.play();

}*/

//--------------------------------------------------------------
void ofApp::update(){

    while(receiver.hasWaitingMessages()){
        
        ofHideCursor();
        ofxOscMessage m;
        receiver.getNextMessage(m);
        int receivedInt = m.getArgAsInt(0);
        
        ofLog() << "received: " << m.getArgAsInt(0) << " var is: " << receivedInt << endl;
        
        if(receivedInt > 0 && receivedInt < 12)
        {
            indexLeft = ofToString(receivedInt);
            //indexLeft = (int)m.getArgAsInt(0);
            ofLog() << "indexLeft is: " << indexLeft << endl;
        }
    }
    
  if (indexLeft != currentLeft){
    vplayerLeft.stop();
    vplayerLeft.close();
    filenameLeft = XML.getValue("film[@id=" + indexLeft + "]/filename");
    ofLog() << "filename left: " << filenameLeft << endl;
    vplayerLeft.load("films/" + filenameLeft);
      vplayerLeft.setLoopState(OF_LOOP_NONE);
    vplayerLeft.play();
    currentLeft = indexLeft;
  }
/*
  if (indexRight != currentRight){
    vplayerRight.stop();
    vplayerRight.close();
    filenameRight = XML.getValue("film[@id=" + indexRight + "]/filename");
    ofLog() << "filename right: " << filenameRight << endl;
    vplayerRight.load("films/" + filenameRight);
    vplayerRight.setLoopState(OF_LOOP_NONE);
    vplayerRight.play();
    currentRight = indexRight;
  }
*/
  vplayerLeft.update();
  //vplayerRight.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  if(vplayerLeft.getIsMovieDone())
  {
    
  }
  else{
//      vplayerLeft.draw(0,0, 768, 1024);
      if(alternator[ofToInt(indexLeft)-1] > 0)
      {
          vplayerLeft.draw(674 + 1920,0, 572, 1080);
      }
      //vplayerLeft.draw(450, 0, 380, 720);
      else {
          vplayerLeft.draw(674, 0, 572, 1080);
      }
  }
}

//--------------------------------------------------------------
/*
void ofApp::drawRight(ofEventArgs &args){

//  vplayerRight.draw(0,0, 768, 1024);
}
*/
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  ofLog() << "Key Pressed: " << key << endl;

  if (key >= 49 && key <= 58){
    int i = key - 48;
    string c = to_string(i);
    ofLog() << "index: " << c << endl;
    /*if (i % 2 == 0) {
      indexRight = c;
    } else {*/
      indexLeft = c;
    //}
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
