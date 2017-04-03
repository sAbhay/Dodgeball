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
#include "ofApp.h"

class Player
{
    private:
        ofVec3f pos;
        ofVec3f size;
        ofEasyCam cam;
        bool ducked;
        bool out;
        int team;
        float speed;
        void checkBoundaries();

    
    public:
        Player(ofVec3f start, int t);
        ~Player();
        void moveFoward();
        void moveBack();
        void moveLeft();
        void moveRight();
        void jump();
        void duck();
        void update();
        void pickUpBall(Ball b);
        void checkIfHit(Ball b);
    
        void setDucked(bool d) {ducked = d;}
        bool ducked() {return ducked;}
};

#endif /* player_hpp */
