#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxEconomics.h"

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
    
    
    ofxEconomics            economics;
    
    ofVideoPlayer           media;
    bool                    isPlaying;
    bool                    isFullscreen;
    
    ofParameterGroup        mediaSettingsA;
    ofParameter<int>        innerA;
    ofParameter<int>        packA;
    ofParameter<float>      widthPrcA;
    ofParameter<float>      heightPrcA;
    ofParameter<ofColor>    tintA;
    //
    ofParameterGroup        mediaSettingsB;
    ofParameter<int>        innerB;
    ofParameter<int>        packB;
    ofParameter<float>      widthPrcB;
    ofParameter<float>      heightPrcB;
    ofParameter<ofColor>    tintB;
    //
    ofxPanel                gui;
    
    void togglePlay();
	void pause();
	void play();
    void drawGlitchedVideo(ofVideoPlayer & video, float width, float height, float innerFormat, float packFormat);
};
