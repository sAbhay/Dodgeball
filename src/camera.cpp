//
//  camera.cpp
//  FPDodgeball
//
//  Created by Abhay Singhal on 4/6/17.
//
//

#include "camera.hpp"
#include "ofMain.h"

Camera::Camera(ofVec3f pos)
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
    
    mouse.x = prevMouse.x = ofGetMouseX();
    mouse.y = prevMouse.y = ofGetMouseY();
    
    cam = ofCamera();
}

Camera::Camera()
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
    
    mouse.x = prevMouse.x = ofGetMouseX();
    mouse.y = prevMouse.y = ofGetMouseY();
    
    cam = ofCamera();
}


Camera::~Camera()
{
    
}

void Camera::update()
{
    mouse.x = ofGetMouseX();
    mouse.y = ofGetMouseY();
    
    pan += ofMap(mouse.x - prevMouse.x, 0, ofGetWidth(), 0, TWO_PI) * sensitivity;
    tilt += ofMap(mouse.y - prevMouse.y, 0, ofGetHeight(), 0, PI) * sensitivity;
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

float Camera:: clamp(float x, float min, float max){
    if (x > max) return max;
    if (x < min) return min;
    return x;
}

void Camera::applyGravity(float change, float ground)
{
    if(position.y < ground)
    {
        position.y += change;
    }
}

void Camera::begin()
{
    cam.begin();
}

void Camera::end()
{
    cam.end();
}

void Camera::moveUp(float rate)
{
    velocity += up * rate;
}
