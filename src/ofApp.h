#pragma once

#include "ofMain.h"
#include "player.hpp"
#include "ball.hpp"
#include "bot.hpp"

class ofApp : public ofBaseApp
{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    private:
        Player player;
        std::vector<Ball> b;
        std::vector<Bot> bots;
        std::vector<ofVec2f> botpos;
        ofVec3f dimensions = ofVec3f(10000, 2000, 10000);
        bool m[4] = {false, false, false, false};
        int counter;
        int level;
    
        void restart();
};
