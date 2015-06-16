#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxEconomics.h"

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
    
    //-------------------------------------------
    
    ofxEconomics            economics;
    ofVideoPlayer           video;
    bool                    isPlaying;
    bool                    isFullscreen;
    bool                    isGlitch;
    
    ofParameter<int>        videoWidth;
    ofParameter<int>        videoHeight;
    
    ofxPanel                gui;
    ofParameter<int>        innerA;
    ofParameter<int>        packA;
    ofParameter<float>      widthPrcA;
    ofParameter<float>      heightPrcA;
    ofParameter<ofColor>    tintA;
    
    ofParameter<int>        innerB;
    ofParameter<int>        packB;
    ofParameter<float>      widthPrcB;
    ofParameter<float>      heightPrcB;
    ofParameter<ofColor>    tintB;
    
    float                   innerAnimatorA, packAnimatorB, heightBAnimator;
    ofxFloatSlider          animationDecay;
    
    //-------------------------------------------
    
    void togglePlay();
	void pause();
	void play();
    void drawGlitchedVideo(ofVideoPlayer & video, float width, float height, float innerFormat, float packFormat);
    void onEconomicFall(float & difference);
};
