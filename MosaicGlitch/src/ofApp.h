#pragma once

#include "ofMain.h"
#include "ofQTKitPlayer.h"
#include "ofImage.h"
#include "ofxGui.h"
#include "Tile.h"



class ofApp : public ofBaseApp{
    
public:
    
    //------------------------------------------------------
    
    void setup();
    void update();
    void draw();
    
    //------------------------------------------------------
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //------------------------------------------------------
    
    ofQTKitPlayer           video;
    ofImage                 currentFrame, currentTile;
    std::vector<Tile>       tileArray;
    void                    initTiles();
    
    //------------------------------------------------------
    
    ofxPanel                gui;
    ofxIntSlider            colours, pos;
    ofxFloatSlider          scale;
    
    int video_width = 800;
    int video_height = 450;
    
    //------------------------------------------------------
    
    int                     numTiles, numTilesX, numTilesY;
    int                     sourceWidth, sourceHeight, displayWidth, displayHeight;
    bool                    isGlitch, isPlaying, isFullscreen;
    
    
};
