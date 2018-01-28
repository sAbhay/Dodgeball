//
//  player.hpp
//  FPDodgeball
//
//  Created by Abhay Singhal on 3/31/17.
//
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ball.hpp"
#include "camera.hpp"

class Player
{
    private:
        CeasyCam cam;

    protected:
        ofVec3f pos;
        ofVec3f size;
        bool ducked;
        bool hit;
        int team;
        float speed;
        void checkBoundaries();
        float power;
        ofVec3f d;
        bool oscillating;
        bool holdingBall;
    
    public:
        Player();
        Player(ofVec2f start, int t, ofVec3f& dimensions);
        ~Player();
        void moveForward();
        void moveBack();
        void moveLeft();
        void moveRight();
        void jump();
        void duck();
        void update();
        void pickUpBall(Ball &b);
        void carryBall(Ball &b);
        void checkIfHit(Ball &b);
        void throwBall(Ball &b);
        void oscillatePower();
        void camera();
    
        void setDucked(bool d) {ducked = d;}
        bool isDucked() {return ducked;}
        void beginCam() {cam.begin();}
        void endCam() {cam.end();}
        bool holdsBall() {return holdingBall;}
        ofVec3f getPos() {return pos;}
};

#endif /* player_hpp */
