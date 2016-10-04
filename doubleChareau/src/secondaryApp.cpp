#include "secondaryApp.h"

//--------------------------------------------------------------
void secondaryApp::setup(){
    
    vid.load("movies/moviehap2.mov");
    vid.play();
}

//--------------------------------------------------------------
void secondaryApp::update(){
    
    vid.update();
    
}

//--------------------------------------------------------------
void secondaryApp::draw(){
    
    vid.draw(0,0, 950, 712);
    
}

//--------------------------------------------------------------
void secondaryApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void secondaryApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void secondaryApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void secondaryApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void secondaryApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void secondaryApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void secondaryApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void secondaryApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void secondaryApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void secondaryApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void secondaryApp::dragEvent(ofDragInfo dragInfo){
    
}
