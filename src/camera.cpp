//
//  camera.cpp
//  FPDodgeball
//
//  Created by Abhay Singhal on 4/6/17.
//
//

#include "camera.hpp"
#include "ofMain.h"

CeasyCam::CeasyCam(ofVec3f pos, float near, float far)
{
    controllable = true;
    speed = 3.f;
    sensitivity = 1.5f;
    position = ofVec3f(pos.x, pos.y, pos.z);
    up = ofVec3f(0.f, 1.f, 0.f);
    right = ofVec3f(1.f, 0.f, 0.f);
    forward = ofVec3f(0.f, 0.f, 1.f);
    velocity = ofVec3f(0.f, 0.f, 0.f);
    pan = 0.f;
    tilt = 0.f;
    friction = 0.75f;
    
    count = 0;
    
    mouse.x = prevMouse.x = ofGetMouseX();
    mouse.y = prevMouse.y = ofGetMouseY();
    
    cam = ofCamera();
    
    cam.setNearClip(near);
    cam.setFarClip(far);
}

CeasyCam::CeasyCam()
{
    controllable = true;
    speed = 3.f;
    sensitivity = 1.5f;
    position = ofVec3f(0, 0, 0);
    up = ofVec3f(0.f, 1.f, 0.f);
    right = ofVec3f(1.f, 0.f, 0.f);
    forward = ofVec3f(0.f, 0.f, 1.f);
    velocity = ofVec3f(0.f, 0.f, 0.f);
    pan = 0.f;
    tilt = 0.f;
    friction = 0.75f;
    
    count = 0;
    
    mouse.x = prevMouse.x = ofGetMouseX();
    mouse.y = prevMouse.y = ofGetMouseY();
    
    cam = ofCamera();
}


CeasyCam::~CeasyCam()
{
    
}

void CeasyCam::update()
{
    mouse.x = ofGetMouseX();
    mouse.y = ofGetMouseY();
        
    pan += ofMap(mouse.x - prevMouse.x, 0, ofGetWidth(), 0, TWO_PI) * sensitivity;
    tilt -= ofMap(mouse.y - prevMouse.y, 0, ofGetHeight(), 0, PI) * sensitivity;
    tilt = ofClamp(tilt, -PI/2.01f, PI/2.01f);
    
    if (tilt == PI/2) tilt += 0.001f;
    
    forward = ofVec3f(cos(pan), tan(tilt), sin(pan));
    forward.normalize();
    right = ofVec3f(cos(pan - PI/2), 0, sin(pan - PI/2));
    
    prevMouse = ofVec2f(mouse.x, mouse.y);
    
    velocity *= friction;
    position += velocity;
    center = position + forward;
    
    cam.setPosition(position);
    cam.lookAt(center);
}

float CeasyCam::clamp(float x, float min, float max)
{
    if (x > max) return max;
    if (x < min) return min;
    return x;
}

void CeasyCam::applyGravity(float change, float ground)
{
    if(position.y < ground)
    {
        velocity.y += change;
    }
}

void CeasyCam::begin()
{
    cam.begin();
}

void CeasyCam::end()
{
    cam.end();
}

void CeasyCam::moveUp(float rate)
{
    velocity.y += up.y * rate;
}

void CeasyCam::checkBoundaries(ofVec3f& d, ofVec3f& size)
{
    if(position.x <= -d.x/2 + size.x/2) position.x = -d.x/2 + size.x/2;
    if(position.x >= d.x/2 - size.x/2) position.x = d.x/2 - size.x/2;
    if(position.z >= d.z/2 - size.z/2) position.z = d.z/2 - size.z/2;
    if(position.z <= size.z/2) position.z = size.z/2;
}
