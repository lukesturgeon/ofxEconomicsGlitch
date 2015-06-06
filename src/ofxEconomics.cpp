#include "ofxEconomics.h"

ofxEconomics::ofxEconomics() {
    economicState = -1;
    updateThreshold.set("updateThreshold", 0.95f, 0.0f, 1.0f);
    
    // fild the array with random perlin noise
    for(int i = 0; i < 100; i++)
    {
        data.push_back( ofSignedNoise( 0.1*i ) );
    }
    
    randomCounter = data.size();
}

float ofxEconomics::getDataAtPercentage(float prc) {
    return data[ floor(prc*data.size()) ];
}

void ofxEconomics::update()
{
    if(ofRandomf() > updateThreshold)
    {
        // get new data
        float n = ofSignedNoise( 0.1*randomCounter++ );
        data.push_back( n );
        data.pop_front();
        
        // check for increase or decrease based on the last 5 values
        float avg = 0.0f;
        for (int i = 1; i < 6; i++){
            avg += data[ data.size()-i ];
        }
        avg /= 5;
        
        // check for increase or decrease based on all values
        float diff = n-avg;
        
        if (n > avg) {
            economicState = OFX_ECONOMIC_RISE;
            ofNotifyEvent(onEconomicRise, diff);
        }
        else
        {
            economicState = OFX_ECONOMIC_FALL;
            ofNotifyEvent(onEconomicFall, diff);
        }
    }
}

void ofxEconomics::draw(int x, int y)
{
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(x, y);
    
    ofSetColor(60);
    ofRect(0, 0, data.size(), 100);
    
    // draw the data
    ofSetColor(255);
    for(int i = 1; i < data.size(); i++)
    {
        ofLine(i-1, ofMap(data[i-1], -1, 1, 100, 0),
               i, ofMap(data[i], -1, 1, 100, 0) );
    }
    
    if (economicState == OFX_ECONOMIC_FALL){
        ofSetColor(255, 0, 0);
    } else {
        ofSetColor(0, 255, 0);
    }
    ofRect(5, 5, 10, 10);
    
    ofPopStyle();
    ofPopMatrix();
}