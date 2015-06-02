#pragma once

#include "ofMain.h"

class ofxEconomics {
    
public:
    
    ofxEconomics();
    void update();
    void draw(int x, int y);
    
    deque<float> data;
    int randomCounter;
    
};
