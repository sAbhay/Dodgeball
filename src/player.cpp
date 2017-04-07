//
//  player.cpp
//  FPDodgeball
//
//  Created by Abhay Singhal on 3/31/17.
//
//

#include "player.hpp"

Player::Player()
{
    cam = Camera(ofVec3f(0, 0, 0));
    
    pos = cam.position;
    cam.position.y = d.y - (2*size.y/3);
    pos.y = d.y - size.y;
    
    team = 0;
    
    ducked = false;
    out = false;
    
    speed = 0;
    
    size = ofVec3f(100, 300, 100);
    
    d = ofVec3f(0, 0, 0);
    
    power = 0;
}

Player::Player(ofVec2f start, int t, ofVec3f& dimensions)
{
    size = ofVec3f(100, 300, 100);
    
    d = dimensions;
    
    pos.x = start.x;
    pos.y = d.y - size.y;
    pos.z = start.y;
    
    cam = Camera(ofVec3f(start.x, 1000 - (2*size.y/3), start.y));
    
    pos = cam.position;
    pos.y = d.y - size.y;
    
    cam.speed = speed;
    
    team = t;
 
    ducked = false;
    out = false;
    
    speed = 10;
    
    power = 0;
}

Player::~Player()
{
    
}

void Player::moveRight()
{
    cam.moveRight();
}

void Player::moveLeft()
{
    cam.moveLeft();
}

void Player::moveFoward()
{
    cam.moveForward();
}

void Player::moveBack()
{
    cam.moveBack();
}

void Player::jump()
{
    cam.moveUp(2000);
}

void Player::duck()
{
    speed *= 0.5;
    size.y *= 0.5;
}

void Player::checkBoundaries()
{
    if(pos.x <= size.x/2) pos.x = size.x/2;
    if(pos.x >= d.x - size.x/2) pos.x = d.x - size.x/2;
    if(pos.z >= -size.z/2) pos.z = size.z/2;
    if(pos.z <= -d.z + size.z/2) pos.z = -d.z - size.z/2;
}

/*void Player::checkIfHit(Ball* b)
{
    ofVec3f bp = b -> getPos();

    if((bp.y <= pos.y + size.y/2 && bp.y >= pos.y - size.y/2) && ofDist(bp.x, bp.z, pos.x, pos.y) <= size.x/2 + b -> getSize())
    {
        if(b -> isLive())
        {
            out = true;
        }
    }
}*/

/*void Player::pickUpBall(Ball* b)
{
    ofVec3f bp = b -> getPos();
    
    if(ofDist(bp.x, bp.z, pos.x, pos.y) <= 300)
    {
        b -> setPos(pos);
        b -> setLive(true);
    }
}*/

void Player::oscillatePower()
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

/*void Player::throwBall(Ball* b)
{
//    b = Ball(pos, ofVec3f(ofRandom(0, d.x), ofRandom(0, d.y), ofRandom(0, d.z)), power, b.getSize(), &d);
}*/

void Player::update()
{
    checkBoundaries();
    
    if(ducked) duck();
    
    pos = cam.position;
    cam.position.y = d.y - (2*size.y/3);
    pos.y = d.y - size.y;
    
    cam.update();
    
    cam.speed = speed;
    
    cam.applyGravity(0.001, 1000 - (2*size.y/3));
    
    if(oscillating) oscillatePower();
}
