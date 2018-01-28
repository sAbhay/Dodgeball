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
    cam = CeasyCam(ofVec3f(0, 0, 0), 1, 100);
    
    pos = cam.position;
    cam.position.y = -d.y + (2*size.y/3);
    pos.y = -d.y + size.y;
    
    team = 0;
    
    ducked = false;
    hit = false;
    
    speed = 0;
    
    size = ofVec3f(100, 300, 100);
    
    d = ofVec3f(0, 0, 0);
    
    power = 0;
}

Player::Player(ofVec2f start, int t, ofVec3f& dimensions)
{
    d = dimensions;
    size = ofVec3f(100, dimensions.y/3, 100);
    
    pos.x = start.x;
    pos.y = -d.y + size.y;
    pos.z = start.y;
    
    float f = sqrt((d.x * d.x) + (d.z * d.z));
    float far = sqrt((d.y * d.y) + (f * f));
    
    cam = CeasyCam(ofVec3f(start.x, d.y - 5*size.y/6, start.y), 0.1, far);
    
    pos = cam.position;
    pos.y = d.y - size.y;
    
    cam.speed = speed;
    
    team = t;
 
    ducked = false;
    hit = false;
    
    speed = 10;
    
    power = 0;
    
//    std::cout << d;
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

void Player::moveForward()
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
    cam.checkBoundaries(d, size);
}

void Player::checkIfHit(Ball& b)
{
    ofVec3f bp = b.getPos();

    if((bp.y <= pos.y + size.y/2 && bp.y >= pos.y - size.y/2) && ofDist(bp.x, bp.z, pos.x, pos.y) <= size.x/2 + b.getSize())
    {
        if(b.isLive())
        {
            hit = true;
        }
    }
}

void Player::pickUpBall(Ball& b)
{
    b.setHeld(true);
    holdingBall = true;
}

void Player::carryBall(Ball& b)
{
    b.setPos(pos);
}

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

void Player::throwBall(Ball& b)
{
//    b = Ball(pos, ofVec3f(ofRandom(0, d.x), ofRandom(0, d.y), ofRandom(0, d.z)), power, b.getSize(), &d);
    //Ball(ofVec3f st, int s, int radius, ofVec3f& dimensions);
    power = 100;
    holdingBall = false;
    b.setHeld(false);
    ofVec3f target = cam.getForward();
    b.setVel(target*power);
    b.setLive(true);
}

void Player::update()
{
    if(ducked) duck();
    
    cam.position.y = 5*pos.y/6;
    pos = cam.position;
    pos.y = -d.y/2 + size.y;
    
    checkBoundaries();
    
    cam.update();
    
    cam.speed = speed;
    
    cam.applyGravity(0.1f, 5*pos.y/6);
    
    if(oscillating) oscillatePower();
}
