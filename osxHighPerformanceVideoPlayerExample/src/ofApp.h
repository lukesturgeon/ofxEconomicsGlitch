#pragma once

#include "ofMain.h"
#include "ofQTKitPlayer.h"
#include "ofImage.h"

class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//instead of using ofVideoPlayer we use the ofQTKitPlayer directly
		ofQTKitPlayer newsFromSomewhere;
		
        bool frameByframe;
    
    ofImage currentFrame, tempFrame, tile;
    int numTilesX, numTilesY, numTiles, tileWidth, tileHeight;
};

