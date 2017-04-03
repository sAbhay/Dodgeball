//
//  ball.cpp
//  FPDodgeball
//
//  Created by Abhay Singhal on 3/31/17.
//
//

#include "ball.hpp"

Ball::Ball(ofVec3f start, ofVec3f t, int s, int radius, ofVec3f* dimensions)
{
    pos = ofVec3f(start.x, start.y, start.z);
    target = t;
    vel = start - target;
    speed = s;
    
    vel.normalize();
    vel *= speed;
    
    curvelim = ofVec2f(ofRandom(-PI, PI), ofRandom(-PI, PI));
    curve = ofVec2f(0, 0);
    
    d = *dimensions;
    
    restitution = 0.9;
    r = radius;
    m = 2*r;
}

Ball::~Ball()
{
    
}

void Ball::display()
{
    ofDrawSphere(pos.x, pos.y, pos.z, r);
}

void Ball::move()
{
    curve.x += curvelim.x/ofDist(pos.x, pos.y, pos.z, target.x, target.y, target.z);
    curve.y += curvelim.y/ofDist(pos.x, pos.y, pos.z, target.x, target.y, target.z);

    vel.x += cos(curve.x) * speed;
    vel.y += sin(curve.y) * speed;
    
    pos += vel;
    
    pos.y -= 1;
}

void Ball::checkCollision(Ball b)
{
    if(ofDist(pos.x, pos.y, pos.z, b.pos.x, b.pos.y, b.pos.z) < r + b.r)
    {
        ofVec3f temp[] = {pos - b.pos, ofVec3f(-temp[0].x, -temp[0].y, -temp[0].z)};
        
        for(int i = 0; i < 2; i++)
        {
            temp[i].normalize();
        }
        
        temp[0] *= b.vel.length() * restitution;
        temp[1] *= vel.length() * restitution;
        
        vel = temp[0];
        b.vel = temp[1];
    }
}

void Ball::checkBoundaries()
{
    if(pos.x <= 0 || pos.x >= d.x) vel.x *= -restitution;
    if(pos.y <= 0 || pos.y >= d.y) vel.y *= -restitution;
    if(pos.z <= 0 || pos.z >= d.y) vel.z *= -restitution;
}

void Ball::update()
{
    checkBoundaries();
    move();
    display();
}