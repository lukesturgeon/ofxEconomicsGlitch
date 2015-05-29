#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxTLVideoGlitch.h"

class ofApp : public ofBaseApp{
    
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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxTLVideoGlitch* media;
    bool isPlaying;
    
    ofxIntSlider inner;
    ofxIntSlider pack;
    ofxFloatSlider widthPrc;
    ofxFloatSlider heightPrc;
    ofxPanel gui;
    
    void setupGUI();
	void togglePlay();
	void pause();
	void play();
};
