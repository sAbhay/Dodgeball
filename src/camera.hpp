//
//  camera.hpp
//  FPDodgeball
//
//  Created by Abhay Singhal on 4/6/17.
//
//

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include "ofMain.h"

class CeasyCam
{
    private:
        ofCamera cam;

        ofVec3f center;
        ofVec3f up;
        ofVec3f right;
        ofVec3f forward;
        ofVec2f mouse;
        ofVec2f prevMouse;
    
        float clamp(float x, float min, float max);
    
    public:
        CeasyCam(ofVec3f pos, float near, float far);
        CeasyCam();
        ~CeasyCam();
    
        bool controllable;
        float speed;
        float sensitivity;
        ofVec3f position;
        float pan;
        float tilt;
        ofVec3f velocity;
        float friction;
    
        void update();
        void applyGravity(float change, float ground);
        void begin();
        void end();
        void setPosition(ofVec3f pos){position = pos;}
        void checkBoundaries(ofVec3f& d, ofVec3f& size);
    
        void moveForward(){velocity += forward * speed;}
        void moveBack(){velocity -= forward * speed;}
        void moveLeft(){velocity += right * speed;}
        void moveRight(){velocity -= right * speed;}
        void moveUp(float rate);
        ofVec3f getForward(){return forward;}
        ofVec3f getUp() {return up;}
};


#endif /* camera_hpp */
