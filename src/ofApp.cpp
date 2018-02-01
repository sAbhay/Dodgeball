#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    player = Player(ofVec3f(-dimensions.x/2, dimensions.z/4), 0, dimensions);
    
    for(int i = 0; i < 10; i++)
    {
        bots[i] = Bot(ofVec3f(-dimensions.x/2 + i*dimensions.x/10 + dimensions.x/20, -dimensions.z/4), 1, dimensions, i);
    }
    
    for(int i = 0; i < 20; i++)
    {
        int size = (int) ofRandom(30, 50);
    
        b[i] = Ball(ofVec3f(-dimensions.x/2 + i*dimensions.x/20 + dimensions.x/40,  -dimensions.y/2 + size, 0), 1, size, dimensions);
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
    
    for(int i = 0; i < 10; i++)
    {
        botpos[i] = ofVec2f(bots[i].getPos().x, bots[i].getPos().z);
    
        for(int j = 0; j < 10; j++)
        {
            if(i != j)
            {
                bots[i].checkCollision(bots[j]);
            }
        }
        
        if(bots[i].findClosestBall(b) != -1)
        {
            if(!bots[i].holdsBall())
            {
                int index = bots[i].findClosestBall(b);
                
                if(b[index].findClosestBot(botpos) == bots[i].getIndex())
                {
                    bots[i].setRunning(false);
                    bots[i].moveTowards(b[index].getPos());
                }
                else
                {
                    bots[i].setRunning(true);
                }
            }
        }
        
        for(int j = 0; j < 20; j++)
        {
            bots[i].checkIfHit(b[j]);
        
            ofVec3f bp = b[j].getPos();
            ofVec3f p = bots[i].getPos();
    
            if(!bots[i].holdsBall())
            {
                if(ofDist(bp.x, bp.y, bp.z, p.x, p.y, p.z) <= 500 && !b[j].isHeld())
                {
                    if(!b[j].isLive())
                    {
                        bots[i].pickUpBall(b[j]);
                    }
                    else
                    {
                        if(b[j].getThrower() == -1) bots[i].dodge(b[j]);
                    }
                }
            }
            else
            {
                if(b[j].getHolder() == i)
                {
                    bots[i].throwBall(b[j], player.getPos());
                }
            }
        }
        
        bots[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    player.beginCam();
    
    ofBackground(0);
    if(player.isHit()) ofBackground(0, 255, 0);
    ofNoFill();
    ofSetColor(255);
    ofDrawBox(0, 0, 0, dimensions.x, dimensions.y, dimensions.z);
    ofDrawLine(-dimensions.x/2, -dimensions.y/2, 0, dimensions.x/2, -dimensions.y/2, 0);
    
    for(int i = 0; i < 20; i++)
    {
        if(b[i].getThrower() != -1) player.checkIfHit(b[i]);
        
        if(b[i].isHeld())
        {
            if(b[i].getHolder() != -100)
            {
                if(b[i].getHolder() == -1)
                {
                    player.carryBall(b[i]);
                }
                else
                {
                    bots[b[i].getHolder()].carryBall(b[i]);
                }
            }
        }
        
        for(int j = 0; j < 20; j++)
        {
            if(i != j)
            {
                b[i].checkCollision(b[j]);
            }
        }
        
        b[i].update();
    }
    
    for(int i = 0; i < 10; i++)
    {
        bots[i].display();
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
                if(ofDist(bp.x, bp.y, bp.z, p.x, p.y, p.z) <= 500 && !b[i].isHeld())
                {
                    if(b[i].isLive())
                    {
                        bots[b[i].getThrower()].setHit(true);
                        if(player.isHit()) player.setHit(false);
                    }
                    
                    player.pickUpBall(b[i]);
                }
            }
            else
            {
                if(b[i].isHeld() && b[i].getHolder() == -1)
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
