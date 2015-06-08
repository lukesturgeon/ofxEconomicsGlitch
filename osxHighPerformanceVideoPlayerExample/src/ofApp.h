#pragma once

#include "ofMain.h"
#include "ofQTKitPlayer.h"
#include "ofImage.h"
#include "ofxGui.h"
#include "Tile.h"
#include <math.h>

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
    
    void initTiles(int numX, int numY, int srcW, int srcH, int dstW, int dstH);
    
//    ofxFloatSlider radius;
//    ofxColorSlider color;
//    ofxVec2Slider center;
//    ofxToggle filled;
//    ofxButton twoCircles;
//    ofxButton ringButton;
//    ofxLabel screenSize;
    
    ofxPanel gui;
    ofxIntSlider numTilesWidth;
    
    //instead of using ofVideoPlayer we use the ofQTKitPlayer directly
    ofQTKitPlayer newsFromSomewhere;
    
    bool isPaused;
    
    bool isFullScreen;

    ofImage currentFrame, tempFrame;
    
    Tile theTile;

    std::vector<Tile> tileArray;
    
    deque<ofImage> tiles;
    
    int numTilesX, numTilesY, numTiles, tileGrabWidth, tileGrabHeight, tileDispWidth, tileDispHeight;
    
    int slideX, slideY, grabX, grabY;
    
    int displayWidth, displayHeight;
};

