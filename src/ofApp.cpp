#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    counter = 0;
    level = 0;
    
    player = Player(ofVec3f(-dimensions.x/2, dimensions.z/4), 0, dimensions);
    
    restart();
}

//--------------------------------------------------------------
void ofApp::update()
{
    if(m[0]) player.moveForward();
    if(m[1]) player.moveBack();
    if(m[2]) player.moveLeft();
    if(m[3]) player.moveRight();
    
    player.update();
    
    for(int i = 0; i < bots.size(); i++)
    {
        if(bots.at(i).isHit())
        {
            bots.erase(bots.begin() + i);
        }
    }
    
    cout << bots.size() << endl;
    
    for(int i = 0; i < bots.size(); i++)
    {
        bots.at(i).setIndex(i);
    
        botpos.push_back(ofVec2f(bots.at(i).getPos().x, bots.at(i).getPos().z));
    
        for(int j = 0; j < bots.size(); j++)
        {
            if(i != j)
            {
                bots.at(i).checkCollision(bots.at(j));
            }
        }
        
        if(bots.at(i).findClosestBall(b) != -1)
        {
            if(!bots.at(i).holdsBall())
            {
                int index = bots.at(i).findClosestBall(b);
                
                if(b.at(index).findClosestBot(botpos) == bots.at(i).getIndex())
                {
                    bots.at(i).setRunning(false);
                    bots.at(i).moveTowards(b.at(index).getPos());
                }
                else
                {
                    bots.at(i).setRunning(true);
                }
            }
        }
        
        for(int j = 0; j < b.size(); j++)
        {
            bots.at(i).checkIfHit(b.at(j));
        
            ofVec3f bp = b.at(j).getPos();
            ofVec3f p = bots.at(i).getPos();
    
            if(!bots.at(i).holdsBall())
            {
                if(ofDist(bp.x, bp.y, bp.z, p.x, p.y, p.z) <= 500 && !b.at(j).isHeld())
                {
                    if(!b.at(j).isLive())
                    {
                        bots.at(i).pickUpBall(b.at(j));
                    }
                    else
                    {
                        if(b.at(j).getThrower() == -1) bots.at(i).dodge(b.at(j), level);
                    }
                }
            }
            else
            {
                if(b.at(j).getHolder() == i)
                {
                    bots.at(i).throwBall(b.at(j), player.getPos());
                }
            }
        }
        
        bots.at(i).update();
    }
    
    botpos.clear();
    
    for(int i = 0; i < b.size(); i++)
    {
        if(b.at(i).getThrower() != -1) player.checkIfHit(b.at(i));
        
        if(b.at(i).isHeld())
        {
            if(b.at(i).getHolder() != -100)
            {
                if(b.at(i).getHolder() == -1)
                {
                    player.carryBall(b.at(i));
                }
                else
                {
                    bots.at(b.at(i).getHolder()).carryBall(b.at(i));
                }
            }
        }
        
        for(int j = 0; j < b.size(); j++)
        {
            if(i != j)
            {
                b.at(i).checkCollision(b.at(j));
            }
        }
        
        b.at(i).update();
    }
    
    counter++;
    
    if(counter == (int) ((20*ofGetFrameRate()/b.size())*10))
    {
        int size = (int) ofRandom(30, 50);
        b.push_back(Ball(ofVec3f(ofRandom(-dimensions.x/2, dimensions.x/2),  dimensions.y/4 + size, ofRandom(-dimensions.z/2, 0)), 1, size, dimensions));
        counter = 0;
    }
    
    if(bots.size() == 0) restart();
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
    
    for(int i = 0; i < b.size(); i++)
    {
        b.at(i).display();
    }
    
    for(int i = 0; i < bots.size(); i++)
    {
        bots.at(i).display();
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
        for(int i = 0; i < b.size(); i++)
        {
            ofVec3f bp = b.at(i).getPos();
            ofVec3f p = player.getPos();
    
            if(!player.holdsBall())
            {
                if(ofDist(bp.x, bp.y, bp.z, p.x, p.y, p.z) <= 500 && !b.at(i).isHeld())
                {
                    if(b.at(i).isLive())
                    {
                        bots.at(b.at(i).getThrower()).setHit(true);
                        if(player.isHit()) player.setHit(false);
                    }
                    
                    player.pickUpBall(b.at(i));
                }
            }
            else
            {
                if(b.at(i).isHeld() && b.at(i).getHolder() == -1)
                {
                    player.throwBall(b.at(i));
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

void ofApp::restart()
{
    level++;
    counter = 0;
    
    b.clear();
    bots.clear();
    
    player.setHoldingBall(false);
    
     for(int i = 0; i < level; i++)
    {
        bots.push_back(Bot(ofVec3f(-dimensions.x/2 + i*dimensions.x/level + dimensions.x/(2*level), -dimensions.z/4), 1, dimensions, i));
    }
    
    for(int i = 0; i < 20; i++)
    {
        int size = (int) ofRandom(30, 50);
    
        b.push_back(Ball(ofVec3f(-dimensions.x/2 + i*dimensions.x/20 + dimensions.x/40, -dimensions.y/2 + size, 0), 0, size, dimensions));
    }
}
