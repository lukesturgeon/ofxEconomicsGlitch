#pragma once

#include "ofMain.h"
#include "ofxEconomics.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //-----------------------------------------
    
    ofxPanel                gui;
    ofParameter<float>      yOffsetAmount;
    ofParameter<float>      yOffsetSpeed;
    ofParameter<float>      yElasticity;
    ofParameter<ofColor>    col1;
    ofParameter<ofColor>    col2;
    ofParameter<ofColor>    col3;
    ofParameter<int>        videoWidth;
    ofParameter<int>        videoHeight;
    
     //-----------------------------------------
    
    
    ofVideoPlayer       video;
    ofTexture           texture;
    ofxEconomics        economics;
    bool                isPlaying;
    bool                isFullscreen;
    bool                isGlitch;
    bool                isFreeScale;
    bool                isVideoFinished;
    deque<float>        timeline;
    float               glitchOffset;
    
    void play();
    void pause();
    void togglePlay();
    void onEconomicFall(float & difference);
    void onEconomicRise(float & difference);
    
};
