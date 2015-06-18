#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define NUM_DATA 100
#define OFX_ECONOMIC_RISE 1
#define OFX_ECONOMIC_FALL 0
#define PORT 6666

class ofxEconomics {
    
public:
    
    ofxEconomics();
    void update();
    void draw(int x, int y);
    void resetHistory();
    float getDataAtPercentage(float p);
    
    ofEvent<float> onEconomicRise;
    ofEvent<float> onEconomicFall;
    
    ofxOscReceiver receiver;
    
    deque<float> data;
    
    float minValue, maxValue;
    bool isEmpty;
    
//    ofParameter<float> updateThreshold;
    
};
