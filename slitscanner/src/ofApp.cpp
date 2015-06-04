#include "ofApp.h"

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


int video_width = 800;
int video_height = 450;

deque<int> draw_positions (400);



//--------------------------------------------------------------
void ofApp::setup()
{
    isFullscreen = false;
    isPlaying = false;
    
    // setup the videoplayer
    video.loadMovie("/Users/lukesturgeon/Dropbox/4 - RCA/11 - Glitch Films/2 - Production/Assets/BigFreezeSecondEditSansSon.mp4");
    video.setLoopState(OF_LOOP_NORMAL );
    play();
    
    texture.allocate(video_width, video_height, GL_RGB);
    
    gui.setup();
    gui.add( yOffsetAmount.set("y offset", 400, 0, 1000) );
}

//--------------------------------------------------------------
void ofApp::update()
{
    video.update();
    
    if (video.isFrameNew())
    {
        texture.loadData( video.getPixelsRef() );
    }
    
    economics.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    if (noGlitch)
    {
        // draw the original
        video.draw((ofGetWidth() - video.width) / 2, (ofGetHeight() - video.height) / 2, video.width, video.height);
    }
    else
    {
        // draw a glitch
        //texture.draw((ofGetWidth() - video.width) / 2, (ofGetHeight() - video.height) / 2, video.width, video.height);
        
        ofSetColor(255);
        
        float yOffset = 0;
        
        for (int x = 0; x < video_width; x++) {
            // draw a section
            yOffset = ofMap(economics.getValueAt((float)x/video_width), -1.0f, 1.0f, 0.0f, 1.0f);
            texture.drawSubsection(x, yOffsetAmount * yOffset, 1, video_height, x, 0);
            yOffset++;
        }
        
        economics.draw(10,ofGetHeight()-130);
        
        // debugger
        ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, ofGetHeight()-10);
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 'f')
    {
        isFullscreen = !isFullscreen;
        ofSetFullscreen(isFullscreen);
	}
    if (key == 'o')
    {
        noGlitch = !noGlitch;
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
void ofApp::mouseReleased(int x, int y, int button){
    
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
