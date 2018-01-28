#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    player = Player(ofVec3f(ofGetWidth()/2, -100), 0, dimensions);
    
    for(int i = 0; i < 20; i++)
    {
        int size = (int) ofRandom(30, 50);
    
        b[i] = Ball(ofVec3f(-dimensions.x/2 + i*dimensions.x/20 + dimensions.x/40,  -dimensions.y/2 + size, 0), 1, size, dimensions);
//        b[i] = Ball(ofVec3f(ofRandom(-dimensions.x/2, dimensions.x/2), ofRandom(-dimensions.y/2, dimensions.y/2), ofRandom(-dimensions.z/2, dimensions.z/2)), 30, size, dimensions);
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    if(m[0]) player.moveForward();
    if(m[1]) player.moveBack();
    if(m[2]) player.moveLeft();
    if(m[3]) player.moveRight();
    
    player.update();
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
        
        if(b[i].isHeld())
        {
            player.carryBall(b[i]);
        }
        
        for(int j = 0; j < 20; j++)
        {
            if(i != j)
            {
                b[i].checkCollision(b[j]);
            }
        }
    }
    
    player.endCam();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'w' || key == 'W')
    {
        m[0] = true;
    }
    
    if(key == 's' || key == 'S')
    {
        m[1] = true;
    }
    
    if(key == 'a' || key == 'A')
    {
        m[2] = true;
    }
    
    if(key == 'd' || key == 'D')
    {
        m[3] = true;
    }
    
    if(key == OF_KEY_LEFT_SHIFT)
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

    if(key == 'w' || key == 'W')
    {
        m[0] = false;
    }
    
    if(key == 's' || key == 'S')
    {
        m[1] = false;
    }
    
    if(key == 'a' || key == 'A')
    {
        m[2] = false;
    }
    
    if(key == 'd' || key == 'D')
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

    if(button == 0)
    {
        for(int i = 0; i < 20; i++)
        {
            ofVec3f bp = b[i].getPos();
            ofVec3f p = player.getPos();
    
            if(!player.holdsBall())
            {
                if(ofDist(bp.x, bp.z, p.x, p.z) <= 500)
                {
                    player.pickUpBall(b[i]);
                }
            }
            else
            {
                if(b[i].isHeld())
                {
                    player.throwBall(b[i]);
                }
            }
        }
    }
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
