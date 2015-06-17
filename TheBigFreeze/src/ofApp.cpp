#include "ofApp.h"


#define DATA_ARRAY_LENGTH 200

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowTitle("The Big Freeze");
    ofBackground(0);
    
    isFullscreen = false;
    isPlaying = false;
    isGlitch = true;
    isFreeScale = false;
    
    // the global video width and height
    videoWidth.set(1280);
    videoHeight.set(720);
    
    // fill the timeline with nothing
    for (int i = 0; i < DATA_ARRAY_LENGTH; i++) {
        timeline.push_back( 0.0f );
    }
    
    // setup the economics numbers
    ofAddListener(economics.onEconomicRise, this, &ofApp::onEconomicRise);
    ofAddListener(economics.onEconomicFall, this, &ofApp::onEconomicFall);
    
    texture.allocate(videoWidth, videoHeight, GL_RGB);
    
    // setup the videoplayer
    video.loadMovie("/Users/lukesturgeon/Dropbox/4 - RCA/11 - Glitch Films/2 - Production/Assets/TheBigFreeze.mp4");
    video.setLoopState(OF_LOOP_NORMAL );
    play();
  
    gui.setup();
    gui.add( yOffsetAmount.set("Y Offset", 30, 0, 500) );
    gui.add( yOffsetSpeed.set("Y Speed", 1, 1, 30) );
    gui.add( yElasticity.set("Elasticity", 0.0005f, 0.0001f, 0.1f) );
    gui.add( economics.updateThreshold.set(0.035f) );
    gui.add( col1.set("colour1", ofColor(162,0,0), ofColor(0), ofColor(255)) );
    gui.add( col2.set("colour2", ofColor(0,0,255), ofColor(0), ofColor(255)) );
    gui.add( col3.set("colour3", ofColor(0,255,0), ofColor(0), ofColor(255)) );
}

//--------------------------------------------------------------
void ofApp::update() {
    
    // update video
    video.update();
    if (video.isFrameNew())
    {
        texture.loadData(video.getPixelsRef());
    }
    
    // update economics
    if (isPlaying){
        economics.update();
        
        for (int i = 0; i < yOffsetSpeed; i++) {
            // update timeline
            timeline.pop_front();
            timeline.push_back(glitchOffset);
            
            if (glitchOffset != 0) {
                glitchOffset += (0 - glitchOffset) * yElasticity;
            }
        }
    }
}


//--------------------------------------------------------------
void ofApp::exit()
{
    ofRemoveListener(economics.onEconomicRise, this, &ofApp::onEconomicRise);
    ofRemoveListener(economics.onEconomicFall, this, &ofApp::onEconomicFall);
}


//--------------------------------------------------------------
void ofApp::draw()
{
    if (isGlitch)
    {
        // draw a glitch
        ofPushMatrix();
        
        if(!isFreeScale)
        {
            // dont scale, center the video
            ofTranslate((ofGetWidth() - videoWidth) / 2, (ofGetHeight() - videoHeight) / 2);
        }
        else
        {
            // do scale to fill screen
            float sw = (float) ofGetWidth() / videoWidth;
            float sh = (float) ofGetHeight() / videoHeight;
//            cout << sw << "," << sh << endl;
            ofScale(sw, sh);
        }
        
        ofEnableBlendMode(OF_BLENDMODE_SCREEN);
        
        //draw video 1
        ofSetColor(col1);
        video.draw(0, 0);
        
        //draw video 2
        ofSetColor(col2);
        
        int colWidth = videoWidth / DATA_ARRAY_LENGTH;
        for (int i = 0; i < DATA_ARRAY_LENGTH; i++)
        {
            texture.drawSubsection(colWidth*i, timeline[ i ]*yOffsetAmount, colWidth, videoHeight, colWidth*i, 0);
        }
        
        // draw video 3
        ofSetColor(col3);
        video.draw(0, 0);
        
        ofDisableBlendMode();
        
        ofPopMatrix();
        
    }
    else
    {
        // draw the original
        ofSetColor(255);
        
        if(isFreeScale)
        {
            video.draw(0,0,ofGetWidth(),ofGetHeight());
        }
        else
        {
            video.draw((ofGetWidth() - video.width) / 2, (ofGetHeight() - video.height) / 2, video.width, video.height);
        }
        
    }
    
    if (!isFullscreen){
        
        // debugger
        ofSetColor(255);
        economics.draw(10,ofGetHeight()-130);
        
        string debugStr = "'f' = fullscreen";
        
        if (isGlitch) {
            debugStr += " | 'g/[click]' = glitch off";
        }
        else {
            debugStr +=  " | 'g/[click]' = glitch on";
        }
        
        debugStr += " | ' ' = toggle pause";
        debugStr += " | 's' = toggle scale";
        debugStr += " | " + ofToString(ofGetFrameRate(), 0) + "fps";
        ofDrawBitmapString(debugStr, 10, ofGetHeight()-10);
        
        gui.draw();
    }
}


//--------------------------------------------------------------
void ofApp::play(){
    isPlaying = true;
    video.setPaused(false);
}

//--------------------------------------------------------------
void ofApp::pause(){
    isPlaying = false;
    video.setPaused(true);
}

//--------------------------------------------------------------
void ofApp::togglePlay(){
    if (isPlaying){
        isPlaying = false;
        video.setPaused(true);
    } else {
        isPlaying = true;
        video.setPaused(false);
    }
}

//--------------------------------------------------------------
void ofApp::onEconomicRise(float &difference){
    // update the glitchOffset which keeps getting added to the timeline
    glitchOffset = difference*10;
    
//    cout << "up " << difference*10 << endl;
}

//--------------------------------------------------------------
void ofApp::onEconomicFall(float &difference){
    // update the glitchOffset which keeps getting added to the timeline
    glitchOffset = difference*10;
    
//    cout << "down " << difference*10 << endl;
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 's')
    {
        isFreeScale = !isFreeScale;
    }
    if (key == 'f')
    {
        isFullscreen = !isFullscreen;
        ofSetFullscreen(isFullscreen);
	}
    if (key == 'g')
    {
        isGlitch = !isGlitch;
    }
    if(key == ' ')
    {
        togglePlay();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    // toggle glitch
    isGlitch = !isGlitch;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    string file = dragInfo.files[0];
    video.loadMovie(file);
}
