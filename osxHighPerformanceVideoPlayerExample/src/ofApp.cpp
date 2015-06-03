#include "ofApp.h"

// High Performance OS X Video Playback Example
//--------------------------------------------------------------
// This example shows how to use the OS X platform specific
// ofQTKitPlayer on its own without the cross platform
// ofVideoPlayer wrapper.  Apps you write in this way won't be
// cross platform, but can be faster for HD videos .
//--------------------------------------------------------------

void ofApp::setup(){
    ofBackground(0, 0, 0);
    
    
    
    // #1 Play videos with an alpha channel. ---------------------------
    // ofQTKitPlayer videos encoded with Alpha channels (e.g. Animation Codec etc).
    // The pixel format MUST be enabled prior to loading!
    // If an alpha channels is not used, setting a non-alpha pixel format
    // (e.g. OF_PIXELS_RGB) will increase performance.
    newsFromSomewhere.setPixelFormat(OF_PIXELS_RGBA);
    
    //# 2 Decode Modes and video loading. -------------------------------
    // If you don't need direct access to pixel data, you can use ofQTKitPlayer's
    // highly optimized internal texture management system.  These mode are not
    // available when using the cross-platform ofVideoPlayer.
    
    // Texture only is fastest, but no pixel access allowed.
    //   ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_TEXTURE_ONLY;
    
    // Pixels and texture together is faster than PIXEL_ONLY and manually uploaded textures.
    ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
    
    newsFromSomewhere.loadMovie("/Users/peterhudson/Desktop/RCA Projects/Rod/movies/NewsFromSomewhereSecondEdit.mp4", decodeMode);
    
    // You can also load movies from URLs.
    // newsFromSomewhere.loadMovie("http://labs.silentlycrashing.net/fingers.mov", decodeMode);
    
    //# 3 Synchronous seeking. ---------------------------
    // Like the legacy player, by default frames are available immediately for display
    // via setFrame().  In many cases when random access via setFrame() is not required,
    // significant speed increases can be gained by disabling synchronous seeking
    // particularly when playing high bitrate HD video.
    
    // In "asynchronous" seek mode, individual frames can still be randomly accessed,
    // but the pixels may not be available immediately without calling update() first.
    
    // newsFromSomewhere.setSynchronousSeeking(false);
    
    newsFromSomewhere.play();
    
    isPaused = false;
    
    isFullScreen = false;
    
    numTilesX = 16;
    numTilesY = 9;
    numTiles = numTilesX*numTilesY;
    tileGrabWidth = newsFromSomewhere.getWidth() / numTilesX;
    tileGrabHeight = newsFromSomewhere.getHeight() / numTilesY;
    
    slideX = 0;
    
    gui.setup("controls");
    gui.add( numTilesWidth.setup("numTilesWidth", 1, 1, 100) );
    
}

//--------------------------------------------------------------
void ofApp::update(){
    newsFromSomewhere.update();
    
    if(newsFromSomewhere.isFrameNew()) {
        currentFrame.setFromPixels( newsFromSomewhere.getPixelsRef() );
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    ofSetHexColor(0xFFFFFF);
//    ofSetHexColor(0x000000);
    
    if (newsFromSomewhere.isLoaded()) {
        if (!isFullScreen) currentFrame.draw(0, 0);
        
        if(newsFromSomewhere.getDecodeMode() != OF_QTKIT_DECODE_TEXTURE_ONLY){ //pixel access will not work in this mode
            // ofSetHexColor(0x000000);
            unsigned char * pixels = newsFromSomewhere.getPixels();
            ofPixelsRef pixelsRef = newsFromSomewhere.getPixelsRef();
            // ofSetColor(ofColor::white);
            if (!isFullScreen) ofPushMatrix();
            if (!isFullScreen) ofTranslate(currentFrame.width, 0);
            
            for(int i = 0; i < displayWidth; i += tileDispWidth ){
                for(int j = 0; j < displayHeight; j += tileDispHeight ){
                    
                    ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255)); //set random tints by changing this!
                    
                    tiles.push_back(tile);
                    
                    tiles.back().cropFrom(currentFrame, i, j, tileGrabWidth, tileGrabHeight);
                    
                    if (isFullScreen) tiles.back().draw(i + ofRandom(0,slideX), j + ofRandom(0,slideX), tileDispWidth, tileDispWidth);
                    
                    if (!isFullScreen) tiles.back().draw(i + ofRandom(0,slideX), j + ofRandom(0,slideX), tileDispWidth, tileDispWidth);
                }
            }
            
            if (tiles.size() > numTiles) {
                tiles.resize(numTiles);
            }
            
            if (!isFullScreen) ofPopMatrix();
        }
    }
    
    //    ofSetColor(ofColor::white);
    if (!isFullScreen) {
    ofSetColor(ofColor::black);
    
    ofDrawBitmapString( ofToString( ofGetFrameRate() ) + "fps", 20, ofGetHeight()-10);
    ofDrawBitmapString( ofToString( numTilesX ) + " x " + ofToString( numTilesY ) + " tiles", 170, ofGetHeight()-10);
    ofDrawBitmapString("duration: " + ofToString(newsFromSomewhere.getPosition() * newsFromSomewhere.getDuration(), 2) + "/" + ofToString(newsFromSomewhere.getDuration(), 2), 320, ofGetHeight()-10);
    ofDrawBitmapString("slide = " + ofToString( slideX ), 620, ofGetHeight()-10);
    
    ofDrawBitmapString("getWindowMode() " + ofToString( ofGetWindowMode() ), 770, ofGetHeight()-10);
    
        gui.draw();

    }
    
    if(newsFromSomewhere.getIsMovieDone()){
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 'f':
            ofToggleFullscreen();
            break;
            
        case OF_KEY_LEFT:
            if(numTilesX > 1) numTilesX--;
            break;
            
        case OF_KEY_RIGHT:
            numTilesX++;
            break;
            
        case OF_KEY_UP:
            numTilesY++;
            break;
            
        case OF_KEY_DOWN:
            if(numTilesY > 1) numTilesY--;
            break;
            
        case '0':
            newsFromSomewhere.firstFrame();
            break;
            
        case '1':
            tempFrame.setFromPixels( newsFromSomewhere.getPixelsRef() );
            break;
            
        case '.':
            slideX++;
            break;
            
        case ',':
            slideX--;
            break;
            
        case '>':
            slideX+=10;
            break;
            
        case '<':
            slideX-=10;
            break;
            
            
        case ' ':
            if(isPaused){
                newsFromSomewhere.setPaused(false);
                isPaused = false;
            } else {
                newsFromSomewhere.setPaused(true);
                isPaused = true;
            }
            break;
            
    }
    numTiles = numTilesX*numTilesY;
    tileGrabWidth = newsFromSomewhere.getWidth() / numTilesX;
    tileGrabHeight = newsFromSomewhere.getHeight() / numTilesY;
    
    switch  ( ofGetWindowMode() ) {
        case 0:
            displayWidth = currentFrame.width;
            displayHeight = currentFrame.height;
            tileDispWidth = tileGrabWidth;
            tileDispHeight = tileGrabHeight;
            isFullScreen = false;
            break;
            
        case 1:
            displayWidth = ofGetWidth();
            displayHeight = ofGetHeight();
            tileDispWidth = displayWidth/numTilesX;
            tileDispHeight = displayHeight/numTilesY;
            isFullScreen = true;
            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
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
    //    string file = dragInfo.files[0];
    //    media.loadMovie(file);
    //    newsFromSomewhere.loadMovie(file, decodeMode);
    
    //    cout << file << endl;
}