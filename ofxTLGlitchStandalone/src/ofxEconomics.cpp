#include "ofxEconomics.h"

ofxEconomics::ofxEconomics()
{
    cout << "new economics model" << endl;
    
    // fild the array with random perlin noise
    for(int i = 0; i < 100; i++)
    {
        data.push_back( ofSignedNoise( 0.1*i ) );
    }
    
    randomCounter = 100;
}

void ofxEconomics::update()
{
    if(ofRandomf() > .98)
    {
        data.push_back( ofSignedNoise( 0.1*randomCounter++ ) );
        data.pop_front();
    }
}

void ofxEconomics::draw(int x, int y)
{
    ofSetColor(60);
    ofRect(x, y, 100, 100);
    
    // draw the data
    ofSetColor(255);
    for(int i = 1; i < 100; i++)
    {
        ofLine(x+i-1, ofMap(data[i-1], -1, 1, y+100, y),
               x+i, ofMap(data[i], -1, 1, y+100, y) );
    }
}