#include "ofxEconomics.h"

#define MIN_VALUE_DEFAULT 1000
#define MAX_VALUE_DEFAULT 0

ofxEconomics::ofxEconomics()
{
    isEmpty = true;
    minValue = MIN_VALUE_DEFAULT;
    maxValue = MAX_VALUE_DEFAULT;
    
    // listen on the given port
	cout << "[OSC] listening for osc on port " << PORT << "\n";
	receiver.setup(PORT);
}

float ofxEconomics::getDataAtPercentage(float prc)
{
    return data[ floor(prc*data.size()) ];
}

void ofxEconomics::update()
{
    // check for waiting messages
	while(receiver.hasWaitingMessages()){
        
        // get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
        // check for data message
		if(m.getAddress() == "/LiveFeeder/Update"){
            
			// expect arg as a float
			float n = ofToFloat( m.getArgAsString(0) );
            
            // if first time, fill the history of the graph
            if(isEmpty){
                // fild the array with random perlin noise
                for(int i = 0; i < NUM_DATA; i++) {
                    data.push_back( n );
                }
                isEmpty = false;
            }
            else
            {
                // just push in the back
                data.push_back( n );
                data.pop_front();
            }
            
            
            if(n < minValue) {
                minValue = n;
            }
            if (n > maxValue){
                maxValue = n;
            }
            
            //            cout << "new value is " << n << endl;
            
            // check for increase or decrease based on the last value
            if (n < data[NUM_DATA-2]) {
                float maxDiff = maxValue-minValue;
                float diff = maxValue-n;
                float norm = ofMap(diff, 0, maxDiff, 0, 1);
                
                ofNotifyEvent(onEconomicFall, norm );
                
            }
            else if (n > data[NUM_DATA-2])
            {
                float maxDiff = maxValue-minValue;
                float diff = maxValue-n;
                float norm = ofMap(diff, 0, maxDiff, 0, 1);
                
                ofNotifyEvent(onEconomicRise, n);
            }
		}
        
    }
}

void ofxEconomics::resetHistory(){
    isEmpty = true;
    minValue = MIN_VALUE_DEFAULT;
    maxValue = MAX_VALUE_DEFAULT;
    
    for(int i = 0; i < NUM_DATA; i++) {
        data.push_back( 0.0f );
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
    
    if(minValue!=maxValue){
        for(int i = 1; i < data.size(); i++)
        {
            ofLine(i-1, ofMap(data[i-1], minValue, maxValue, 100, 0),
                   i, ofMap(data[i], minValue, maxValue, 100, 0) );
        }
    }
    
    ofDrawBitmapString(ofToString(maxValue), 100, 0);
    ofDrawBitmapString(ofToString(minValue), 100, 100);
    ofDrawBitmapStringHighlight(ofToString(data[NUM_DATA-1]), 100, 50);
    
    ofPopStyle();
    ofPopMatrix();
}