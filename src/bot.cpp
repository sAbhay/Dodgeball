//
//  bot.cpp
//  FPDodgeball
//
//  Created by Abhay Singhal on 27/01/18.
//

#include "bot.hpp"

Bot::Bot()
{
    d = ofVec3f(0, 0, 0);
    size = ofVec3f(100, 300, 100);
    
    pos = ofVec3f(0, 0, 0);
    
    team = 0;
 
    ducked = false;
    revert = false;
    hit = false;
    
    speed = 10;
    
    power = 0;
    
    jumping = false;
    count = 0;
    
    index = 0;
    
    holdingBall = false;
    
    colliding = false;
    
    dodgedir = 1;
}

Bot::Bot(ofVec2f start, int t, ofVec3f& dimensions, int i)
{
    d = dimensions;
    size = ofVec3f(100, dimensions.y/3, 100);
    
    pos.x = start.x;
    pos.y = -d.y/2 + size.y/2;
    pos.z = start.y;
    
    team = t;
 
    ducked = false;
    revert = false;
    hit = false;
    
    speed = 10;
    
    power = 0;
    
    jumping = false;
    count = 0;
    
    index = i;
    
    holdingBall = false;
    
    colliding = false;
    
    dodgedir = 1;
}

Bot::~Bot()
{

}

void Bot::moveForward()
{
    pos.z += speed;
}

void Bot::moveBack()
{
    pos.z -= speed;
}

void Bot::moveLeft()
{
    pos.x -= speed;
}

void Bot::moveRight()
{
    pos.x += speed;
}

void Bot::jump()
{
    jumping = true;
    count = 0;
}

void Bot::oscillatePower()
{
    bool powerUp;
    int pPower = power;
    
    if(pPower < power)
    {
        powerUp = true;
    }
    else
    {
        powerUp = false;
    }
    
    if(powerUp && power >= 100) powerUp = false;
    if(!powerUp && power <= 0) powerUp = true;
    
    if(powerUp) power++;
    else power--;
}

void Bot::checkIfHit(Ball &b)
{
    ofVec3f bp = b.getPos();
    
    float d1 = ofDist(bp.x, bp.y, bp.z, pos.x, pos.y - size.y/2, pos.z);
    float d2 = ofDist(bp.x, bp.y, bp.z, pos.x, pos.y + size.y/2, pos.z);
    
    float lineLen = size.y;
    
    float buffer = b.getSize() + size.x;
    
    if (d1+d2 >= lineLen-buffer && d1+d2 <= lineLen+buffer)
    {
        if(b.isLive() && b.getThrower() == -1)
        {
            hit = true;
        }
    }

}

void Bot::checkBoundaries()
{
    if(pos.x <= -d.x/2 + size.x/2)
    {
        pos.x = -d.x/2 + size.x/2;
        
        if(running)
        {
            vel = ofVec3f(ofRandom(-1, 1), 0, ofRandom(-1, 1));
            vel.normalize();
            vel *= speed;
        }
    }
    
    if(pos.x >= d.x/2 - size.x/2)
    {
        pos.x = d.x/2 - size.x/2;
        
        if(running)
        {
            vel = ofVec3f(ofRandom(-1, 1), 0, ofRandom(-1, 1));
            vel.normalize();
            vel *= speed;
        }
    }
    
    if(pos.z >= -size.z/2)
    {
        pos.z = -size.z/2;
        
        if(running)
        {
            vel = ofVec3f(ofRandom(-1, 1), 0, ofRandom(-1, 1));
            vel.normalize();
            vel *= speed;
        }
    }
    
    if(pos.z <= -d.z/2 + size.z/2)
    {
        pos.z = -d.z/2 + size.z/2;
        
        if(running)
        {
            vel = ofVec3f(ofRandom(-1, 1), 0, ofRandom(-1, 1));
            vel.normalize();
            vel *= speed;
        }
    }
}

void Bot::display()
{
    ofNoFill();
    if(!hit) ofSetColor(255);
    else ofSetColor(255, 0, 0);
    ofDrawSphere(pos.x, -d.y/2 + size.y, pos.z, size.x);
    ofDrawCylinder(pos.x, pos.y, pos.z, size.x, size.y);
}

void Bot::pickUpBall(Ball& b)
{
    b.setHeld(true);
    holdingBall = true;
    b.setHolder(index);
}

void Bot::carryBall(Ball& b)
{
    b.setPos(pos);
}

void Bot::throwBall(Ball& b, ofVec3f target)
{
    power = 100;
    holdingBall = false;
    b.setHeld(false);
    b.setCurve(ofVec2f(ofRandom(0, PI), ofRandom(-PI, PI/2)));
    target = target - pos;
    b.setVel((target.normalize() + ofVec3f(0, 0.10, 0))*power);
    b.setLive(true);
    b.setThrower(index);
    b.setHolder(-100);
}

void Bot::update()
{
    if(ducked)
    {
        speed *= 0.5;
        size.y *= 0.5;
        ducked = false;
    }
    
    if(revert)
    {
        speed *= 2;
        size.y *= 2;
        revert = false;
    }
    
    checkBoundaries();
    
    if(jumping)
    {
        if(count <= 12)
        {
            count++;
            pos.y += speed;
        }
        else
        {
            jumping = false;
            pos.y -= 1.5*speed;
            count = 0;
        }
    }
    else
    {
        if(pos.y > (-d.y/2 + size.y/2)) pos.y -= 1.5*speed;
    }
    
    if(oscillating) oscillatePower();
    
    pos += vel;
}

int Bot::findClosestBall(Ball (&b)[20])
{
    int index = -1;
    float shortestDistance = ofDist(pos.x, pos.z, b[0].getPos().x, b[0].getPos().z);

    for(int i = 0; i < 20; i++)
    {
        if(b[i].getPos().z <= 0)
        {
            if(!b[i].isHeld())
            {
                float dist = ofDist(pos.x, pos.z, b[i].getPos().x, b[i].getPos().z);
    
                if(dist <= shortestDistance)
                {
                    shortestDistance = dist;
                    index = i;
                }
            }
        }
    }
    
    if(index == -1) running = true; else running = false;
    
    return index;
}

void Bot::moveTowards(ofVec3f target)
{
    vel = target - pos;
    vel.y = 0;
    vel.normalize();
    vel *= speed;
}

void Bot::checkCollision(Bot &b)
{
    ofVec3f bp = b.getPos();
    float d = ofDist(pos.x, pos.z, bp.x, bp.z);
    
    if(d <= 2*size.x)
    {
        ofVec3f temp = pos - bp;
        temp.normalize();
        temp *= 2*size.x - d;
        pos += temp;
        b.setPos(bp - temp);
        
        colliding = true;
    }
    else colliding = false;
}

void Bot::dodge(Ball &b)
{
    ofVec3f bv = b.getVel();
    bv.y = 0;

    if(dodgedir < 0)
    {
        float temp = -bv.x; // * ((b.getDeviation().x != 0) ? b.getDeviation().x/b.getDeviation().x:1);
        bv.x = bv.z;
        bv.z = temp;
    }
    else
    {
        float temp = bv.x;
        bv.x = -bv.z;
        bv.z = temp;
    }

    vel = bv.normalize() * speed * 40;

//    vel = ofVec3f(bv.x, 0, 0).normalize() * speed * 40;
}
