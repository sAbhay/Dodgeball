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
#include "player.hpp"

class Ball
{
private:
    void display();
    void move();
    void checkBoundaries();
    
    ofVec3f pos;
    ofVec3f vel;
    ofVec3f target;
    ofVec2f curvelim;
    ofVec2f curve;
    int r;
    int m;
    float speed;
    float restitution;
    bool live;
    
    ofVec3f d;

    public:
        Ball();
        Ball(ofVec3f start, ofVec3f target, int s, int radius, ofVec3f& dimensions);
        ~Ball();
        void checkCollision(Ball& b);
        void update();
    
        void setLive(bool l) {live = l;}
        bool isLive() {return live;}
        void setPos(ofVec3f p) {pos = p;}
        ofVec3f getPos() {return pos;}
        float getSize() {return r;}
};

#endif /* ball_hpp */
