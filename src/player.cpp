//
//  player.cpp
//  FPDodgeball
//
//  Created by Abhay Singhal on 3/31/17.
//
//

#include "player.hpp"

Player::Player(ofVec3f start, int t)
{
    pos = start;
    team = t;
 
    ducked = false;
    out = false;
    
    speed = 10;
    
    size = ofVec3f(100, 300, 100);
}

Player::~Player()
{
    
}

void Player::moveRight()
{
    pos.x += speed;
}

void Player::moveLeft()
{
    pos.x -= speed;
}

void Player::moveFoward()
{
    pos.z += speed;
}

void Player::moveBack()
{
    pos.z -= speed;
}

void Player::jump()
{
    if(pos.y <= pos.y + 50)
    {
        pos.y += 1;
    } else
    {
        pos.y -= 1;
    }
}

void Player::duck()
{
    speed /= 2;
    size.y /= 2;
}
