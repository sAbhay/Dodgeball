//
//  ball.hpp
//  FPDodgeball
//
//  Created by Abhay Singhal on 3/31/17.
//
//

#ifndef ball_hpp
#define ball_hpp

#include <stdio.h>
#include "ofMain.h"

class Ball
{
private:
    void display();
    void move();
    void checkBoundaries();
    
    ofVec3f pos;
    ofVec3f vel;
    ofVec3f start;
    ofVec3f target;
    ofVec2f deviation;
    ofVec2f curve;
    int r;
    int m;
    float speed;
    float restitution;
    float friction;
    bool live;
    bool held;
    
    ofVec3f d;

    public:
        Ball();
        Ball(ofVec3f st, int s, int radius, ofVec3f& dimensions);
        ~Ball();
        void checkCollision(Ball& b);
        void update();
    
        void setLive(bool l) {live = l;}
        bool isLive() {return live;}
        void setPos(ofVec3f p) {pos = p;}
        ofVec3f getPos() {return pos;}
        void setVel(ofVec3f v) {vel = v;}
        ofVec3f getVel() {return vel;}
        int getSize() {return r;}
        int getMass() {return m;}
        bool isHeld() {return held;}
        void setHeld(bool h) {held = h;}
        void setCurve(ofVec2f c) {curve = c;}
};

#endif /* ball_hpp */
