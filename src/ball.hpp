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
#include "ofApp.h"

class Ball
{
    public:
        Ball(ofVec3f start, ofVec3f target, int s, int radius, ofVec3f* dimensions);
        ~Ball();
        void checkCollision(Ball b);
        void update();
    
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
        int speed;
        float restitution;
    
        ofVec3f d;
};

#endif /* ball_hpp */
