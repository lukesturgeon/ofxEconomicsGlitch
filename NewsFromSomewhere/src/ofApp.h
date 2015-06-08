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
    void exit();
    
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
    void                    play();
    void                    pause();
    void                    togglePlay();
    void                    initTiles();
    void                    numTilesXChanged(int & newNumX);
    void                    numTilesYChanged(int & newNumY);
    
    //------------------------------------------------------
    
    ofxPanel                gui;
    ofxIntSlider            colours, pos, numTilesX, numTilesY;
    ofxFloatSlider          scale;
    
    int video_width = 800;
    int video_height = 450;
    
    //------------------------------------------------------
    
    int                     numTiles;
    int                     sourceWidth, sourceHeight, displayWidth, displayHeight;
    bool                    isGlitch, isPlaying, isFullscreen;
    
    
};
