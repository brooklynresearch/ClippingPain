#include "secondaryApp.h"

//--------------------------------------------------------------
void secondaryApp::setup(){
    
    movie2.load("movies/updated.mp4");
    movie2.play();
}

//--------------------------------------------------------------
void secondaryApp::update(){
    
    movie2.update();
    
}

//--------------------------------------------------------------
void secondaryApp::draw(){
    
    movie2.draw(0,0, 950, 712);
    
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
