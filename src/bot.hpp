//
//  bot.hpp
//  FPDodgeball
//
//  Created by Abhay Singhal on 27/01/18.
//

#ifndef bot_hpp
#define bot_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ball.hpp"

class Bot
{
    private:
        ofVec3f pos;
        ofVec3f size;
        ofVec3f vel;
        bool ducked;
        bool revert;
        bool hit;
        int team;
        float speed;
        void checkBoundaries();
        float power;
        ofVec3f d;
        bool oscillating;
        bool holdingBall;
        bool jumping;
        int count;
        int index;
        bool colliding;
        bool running;
        float dodgedir;
    
    public:
        Bot();
        Bot(ofVec2f start, int t, ofVec3f& dimensions, int i);
        ~Bot();
        void moveForward();
        void moveBack();
        void moveLeft();
        void moveRight();
        void moveTowards(ofVec3f target);
        void jump();
        void update();
        void checkCollision(Bot &b);
        void pickUpBall(Ball &b);
        void carryBall(Ball &b);
        void checkIfHit(Ball &b);
        void throwBall(Ball &b, ofVec3f target);
        void oscillatePower();
        void display();
        int findClosestBall(Ball (&b)[20]);
        void dodge(Ball &b);
        void setDodgeDir(float d) {dodgedir = d;}
    
        bool isHit() {return hit;}
        void setHit(bool h) {hit = h;}
        void setDucked(bool d) {if(d) ducked = d; else revert = true;}
        bool isDucked() {return ducked;}
        bool holdsBall() {return holdingBall;}
        ofVec3f getPos() {return pos;}
        void setPos(ofVec3f p) {pos = p;}
        bool isColliding() {return colliding;}
        ofVec3f getVel() {return vel;}
        void setVel(ofVec3f v) {vel = v;}
        bool isRunning() {return running;}
        void setRunning(bool r) {running = r;}
};

#endif /* bot_hpp */
