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
    int thrower;
    int holder;
    int claimant;
    ofColor c;
    
    ofVec3f d;

    public:
        Ball();
        Ball(ofVec3f st, int s, int radius, ofVec3f& dimensions);
        ~Ball();
        void checkCollision(Ball& b);
        void display();
        void update();
        int findClosestBot(std::vector<ofVec2f> &b);
    
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
        int getThrower() {return thrower;}
        void setThrower(int t) {thrower = t;}
        void setHolder(int h) {holder = h;}
        int getHolder() {return holder;}
        ofVec2f getDeviation() {return deviation;}
        void setClaimant(int c) {claimant = c;}
        int getClaimant() {return claimant;}
};

#endif /* ball_hpp */
