#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    player = Player(ofVec3f(ofGetWidth()/2, -100), 0, dimensions);
    
    for(int i = 0; i < 20; i++)
    {
        int size = (int) ofRandom(20, 40);
    
//        b[i] = Ball(ofVec3f(i*dimensions.x/20, size, dimensions.z/2), ofVec3f(i*dimensions.x/20, size, dimensions.z/2), 0, size, dimensions);

        b[i] = Ball(ofVec3f(dimensions.x/2, dimensions.y - size, dimensions.z/2), ofVec3f(dimensions.x/2, dimensions.y - size, dimensions.z/2), 0, size, dimensions);
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    player.update();
    
    if(m[0]) player.moveFoward();
    if(m[1]) player.moveBack();
    if(m[2]) player.moveLeft();
    if(m[3]) player.moveRight();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    player.beginCam();
    
    ofBackground(0);
    ofNoFill();
    ofSetColor(255);
    ofDrawBox(0, 0, 0, dimensions.x, dimensions.y, dimensions.z);
    
    for(int i = 0; i < 20; i++)
    {
        b[i].update();
        
//        for(int j )
    }
    
    player.endCam();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'w')
    {
        m[0] = true;
    }
    
    if(key == 's')
    {
        m[1] = true;
    }
    
    if(key == 'a')
    {
        m[2] = true;
    }
    
    if(key == 'd')
    {
        m[3] = true;
    }
    
    if(key == SHIFT)
    {
        player.setDucked(true);
    }
    
    if(key == ' ')
    {
        player.jump();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if(key == 'w')
    {
        m[0] = false;
    }
    
    if(key == 's')
    {
        m[1] = false;
    }
    
    if(key == 'a')
    {
        m[2] = false;
    }
    
    if(key == 'd')
    {
        m[3] = false;
    }

    if(key == OF_KEY_LEFT_SHIFT)
    {
        player.setDucked(false);
    }

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

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
