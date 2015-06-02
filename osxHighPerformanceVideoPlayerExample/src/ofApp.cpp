#include "ofApp.h"

// High Performance OS X Video Playback Example
//--------------------------------------------------------------
// This example shows how to use the OS X platform specific
// ofQTKitPlayer on its own without the cross platform
// ofVideoPlayer wrapper.  Apps you write in this way won't be
// cross platform, but can be faster for HD videos .
//--------------------------------------------------------------

void ofApp::setup(){
    ofBackground(255, 255, 255);
    
    frameByframe = false;
    
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
    
    numTilesX = 16;
    numTilesY = 9;
    numTiles = numTilesX*numTilesY;
    tileWidth = newsFromSomewhere.getWidth() / numTilesX;
    tileHeight = newsFromSomewhere.getHeight() / numTilesY;
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
    
    if (newsFromSomewhere.isLoaded()) {
        currentFrame.draw(0, 0);
        
        if(newsFromSomewhere.getDecodeMode() != OF_QTKIT_DECODE_TEXTURE_ONLY){ //pixel access will not work in this mode
          //  ofSetHexColor(0x000000);
            unsigned char * pixels = newsFromSomewhere.getPixels();
            ofPixelsRef pixelsRef = newsFromSomewhere.getPixelsRef();
           // ofSetColor(ofColor::white);
            ofPushMatrix();
            ofTranslate(currentFrame.width, 0);
            for(int i = 0; i < currentFrame.width; i += tileWidth ){
                for(int j = 0; j < currentFrame.height; j += tileHeight ){

                    ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255)); //set random tints by changing this!
//                    currentFrame.drawSubsection(i, j, tileWidth, tileHeight, i, j);
//                    
//                    //  the following method is VERY slow, ~8fps:
                      tile.cropFrom(currentFrame, i, j, currentFrame.width / numTilesX, currentFrame.height / numTilesY);
                      tile.draw(i,j);
                }
            }
            ofPopMatrix();
        }
    }
    
//    ofSetColor(ofColor::white);
//    currentFrame.drawSubsection(ofGetWidth()/2, ofGetHeight()/2, 100, 100, 0, 0, 400, 400);
    ofSetColor(ofColor::black);
    
    ofDrawBitmapString( ofToString( ofGetFrameRate() ) + "fps", 20, ofGetHeight()-10);
    ofDrawBitmapString( ofToString( numTilesX ) + " x " + ofToString( numTilesY ) + " tiles", 170, ofGetHeight()-10);
    ofDrawBitmapString("duration: " + ofToString(newsFromSomewhere.getPosition() * newsFromSomewhere.getDuration(), 2) + "/" + ofToString(newsFromSomewhere.getDuration(), 2), 320, ofGetHeight()-10);
    if(newsFromSomewhere.getIsMovieDone()){
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 'f':
            frameByframe = !frameByframe;
            newsFromSomewhere.setPaused(frameByframe);
            break;
            
        case OF_KEY_LEFT:
            numTilesX--;
            break;
            
        case OF_KEY_RIGHT:
            numTilesX++;
            break;
            
        case OF_KEY_UP:
            numTilesY++;
            break;
            
        case OF_KEY_DOWN:
            numTilesY--;
            break;
            
        case '0':
            newsFromSomewhere.firstFrame();
            break;
            
        case '1':
            tempFrame.setFromPixels( newsFromSomewhere.getPixelsRef() );
            break;
            
    }
    numTiles = numTilesX*numTilesY;
    tileWidth = newsFromSomewhere.getWidth() / numTilesX;
    tileHeight = newsFromSomewhere.getHeight() / numTilesY;
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
    if(!frameByframe){
        newsFromSomewhere.setPaused(true);
    }
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(!frameByframe){
        newsFromSomewhere.setPaused(false);
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
