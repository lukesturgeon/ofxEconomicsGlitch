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

//--------------------------------------------------------------
void ofApp::getPixel(int horizontal, int vertical, unsigned char *R, unsigned char *G, unsigned char *B, int w, unsigned char *pixels)
{
    int thisPixel;
    thisPixel = 3 * (w * vertical + horizontal);
    *R = pixels[thisPixel];
    *G = pixels[thisPixel+1];
    *B = pixels[thisPixel+2];
}

//--------------------------------------------------------------
void ofApp::setPixel(int horizontal, int vertical, unsigned char R, unsigned char G, unsigned char B, int w, unsigned char *pixels)
{
    int thisPixel;
    thisPixel = 3 * (w * vertical + horizontal);
    pixels[thisPixel] = R;
    pixels[thisPixel+1] = G;
    pixels[thisPixel+2] = B;
}


int video_width = 800;
int video_height = 450;
int draw_position_x = 0;



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
    texpixels = new unsigned char [video_width * video_height * 3];
}

//--------------------------------------------------------------
void ofApp::update()
{
    video.update();
    
    if (video.isFrameNew())
    {
        vidpixels = video.getPixels();
        for (int y = 0; y < video_height; y++) {
            unsigned char r, g, b;
            getPixel(draw_position_x, y, &r, &g, &b, video_width, vidpixels);
            setPixel(draw_position_x, y, r, g, b, video_width, texpixels);
        }
        texture.loadData(texpixels, video_width, video_height, GL_RGB);
        draw_position_x++;
        
        if(draw_position_x > video_width){
            draw_position_x = 0;
        }
    }
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
        texture.draw((ofGetWidth() - video.width) / 2, (ofGetHeight() - video.height) / 2, video.width, video.height);
        
        // debugger
        ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, ofGetHeight()-10);
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
