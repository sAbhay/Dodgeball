//
//  ball.cpp
//  FPDodgeball
//
//  Created by Abhay Singhal on 3/31/17.
//
//

#include "ball.hpp"

Ball::Ball()
{
    pos = ofVec3f(0, 0, 0);
    target = pos;
    vel = pos - target;
    speed = 0;
    
    deviation = ofVec2f(0, 0);
    curve = ofVec2f(0, 0);
    
    d = ofVec3f(0, 0, 0);
    
    restitution = 0;
    r = 0;
    m = 0;
    
    live = false;
}

Ball::Ball(ofVec3f st, int s, int radius, ofVec3f& dimensions)
{
    start = st;
    pos = ofVec3f(st.x, st.y, st.z);
    target = pos;
    vel = pos - target;
    speed = s;
    
    vel.normalize();
    vel *= speed;
    
    d = dimensions;
    
    restitution = 0.5;
    friction = 0.9;
    r = radius;
    m = 2*r;
    
    curve = ofVec2f(ofRandom(0, PI), ofRandom(-PI, PI/2));
    deviation = ofVec2f(0, 0);
    
    live = false;
    held = false;
}

Ball::~Ball()
{
    
}

void Ball::display()
{
    ofFill();
    ofSetColor(255, 0, 0);
    ofDrawSphere(pos.x, pos.y, pos.z, r);
}

void Ball::move()
{
    if(live)
    {
//        curve.x = curvelim.x*ofDist(start.x, start.y, start.z, target.x, target.y, target.z);
//        curve.y = curvelim.y*ofDist(start.x, start.y, start.z, target.x, target.y, target.z);
    
        if(deviation.x < 10 && deviation.y < 10)
        {
            std::cout << curve.x;
            
            deviation.x += (m/80)*cos(curve.x);
            deviation.y += (m/100)*sin(curve.x);
            
            vel.x += (m/80)*cos(curve.x);
            vel.y += (m/100)*sin(curve.y);
        }
    }
    
    pos += vel;
    
    vel.y -= 0.4;
    
    if(pos.y <= -d.y/2 + r)
    {
        vel *= friction;
    }
}

void Ball::checkCollision(Ball& b)
{
    ofVec3f bP = b.getPos();
    ofVec3f bV = b.getVel();
    int bR = b.getSize();
    int bM = b.getMass();

    if(ofDist(pos.x, pos.y, pos.z, bP.x, bP.y, bP.z) < r + bR)
    {
//        ofVec3f temp[] = {pos - bP, ofVec3f(-temp[0].x, -temp[0].y, -temp[0].z)};
//
//        for(int i = 0; i < 2; i++)
//        {
//            temp[i].normalize();
//        }
//
//        temp[0] *= bV.length() * restitution + 10;
//        temp[1] *= vel.length() * restitution + 10;
//
//        vel = temp[0];
//        b.setVel(temp[1]);

        ofVec3f U1x,U1y,U2x,U2y,V1x,V1y,V2x,V2y;

        float m1, m2, x1, x2;
        ofVec3f v1temp, v1, v2, v1x, v2x, v1y, v2y, x(pos - bP);

        x.normalize();
        v1 = vel;
        x1 = x.dot(v1);
        v1x = x * x1;
        v1y = v1 - v1x;
        m1 = m;

        x = x *- 1;
        v2 = bV;
        x2 = x.dot(v2);
        v2x = x * x2;
        v2y = v2 - v2x;
        m2 = bM;

        vel = v1x*(m1-m2)/(m1+m2) + v2x*(2*m2)/(m1+m2) + v1y;
        b.setVel(v1x*(2*m1)/(m1+m2) + v2x*(m2-m1)/(m1+m2) + v2y);
    }
}

void Ball::checkBoundaries()
{
    if(pos.x <= -d.x/2 + r)
    {
        vel.x *= -restitution;
        pos.x = -d.x/2 + r;
        live = false;
    }
    
    if(pos.x >= d.x/2 - r)
    {
        vel.x *= -restitution;
        pos.x = d.x/2 - r;
        live = false;
    }
    
    if(pos.y <= -d.y/2 + r)
    {
        vel.y *= -restitution;
        pos.y = -d.y/2 + r;
        live = false;
    }
    
    if(pos.y >= d.y/2 - r)
    {
        vel.y *= -restitution;
        pos.y = d.y/2 - r;
        live = false;
    }
    
    if(pos.z <= -d.z/2 + r)
    {
        vel.z *= -restitution;
        pos.z = -d.z/2 + r;
        live = false;
    }
    
    if(pos.z >= d.z/2 - r)
    {
        vel.z *= -restitution;
        pos.z = d.z/2 - r;
        live = false;
    }
}

void Ball::update()
{
    checkBoundaries();
    move();
    
    display();
}
