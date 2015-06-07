#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    
    newsFromSomewhere.setPixelFormat(OF_PIXELS_RGBA);
    ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
    newsFromSomewhere.loadMovie("/Users/peterhudson/Desktop/RCA Projects/Rod/movies/NewsFromSomewhereSecondEdit.mp4", decodeMode);
    // newsFromSomewhere.setSynchronousSeeking(false);
    newsFromSomewhere.play();
    numTilesX = 16;
    numTilesY = 9;
    initTiles();
}

//--------------------------------------------------------------
void ofApp::update(){
    newsFromSomewhere.update();
    if(newsFromSomewhere.isFrameNew()) {
        currentFrame.setFromPixels( newsFromSomewhere.getPixelsRef() );
    }

    //display framerate as window title
    std::stringstream strm;
    strm << "fps: " << ofGetFrameRate();
    ofSetWindowTitle(strm.str());
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    for (int i = 0; i < numTiles; i++) {
    //    ofSetColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
        currentTile.cropFrom(currentFrame, tileArray[i].sX, tileArray[i].sY, tileArray[i].sW, tileArray[i].sH);
        currentTile.draw(tileArray[i].dX, tileArray[i].dY, tileArray[i].dW, tileArray[i].dH);
    }
    ofSetColor(0);
    
    for (int i = 0; i < numTiles; i++) {
        ofDrawBitmapString( "i = " + ofToString(i) + "\t" + ofToString(tileArray[i].dX) + " dX\t" + ofToString(tileArray[i].dY)+ " dY\t" +ofToString(tileArray[i].dW)+ " dW\t" +ofToString(tileArray[i].dH)+ " dH\t", 20, 20 + (i*12));
    }
  
    //    ofDrawBitmapString( ofToString( ofGetFrameRate() ) + "fps", 20, displayHeight-10);
}

//--------------------------------------------------------------
void ofApp::initTiles(){
    numTiles = numTilesX * numTilesY;
    displayWidth = ofGetWidth();
    displayHeight = ofGetHeight();
    sourceWidth = newsFromSomewhere.getWidth();
    sourceHeight = newsFromSomewhere.getHeight();
    tileArray.assign(numTiles, Tile());
    for (int i = 0; i < numTiles; i++) {
        tileArray[i].setPos(i, numTiles, numTilesX, numTilesY, sourceWidth, sourceHeight, displayWidth, displayHeight);
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
    }
    
    initTiles();
    
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
    
}
