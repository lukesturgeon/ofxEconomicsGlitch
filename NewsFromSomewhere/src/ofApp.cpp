#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowTitle("News From Somewhere");
    ofBackground(0);
    
    isFullscreen = false;
    isPlaying = false;
    isGlitch = true;
    isSetup = false;
    
    // the global video width and height
    videoWidth.set(800);
    videoHeight.set(450);
    
    // setup economics
    ofAddListener(economics.onEconomicRise, this, &ofApp::onEconomicRise);
    ofAddListener(economics.onEconomicFall, this, &ofApp::onEconomicFall);
    
    // setup video
    video.setPixelFormat(OF_PIXELS_RGBA);
    ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
    video.loadMovie("/Users/lukesturgeon/Dropbox/4 - RCA/11 - Glitch Films/2 - Production/Assets/NewsFromSomewhereFourthEdit.mp4", decodeMode);
    video.setLoopState(OF_LOOP_NORMAL );
    play();
    
    // setup GUI
    numTilesX.addListener(this, &ofApp::numTilesXChanged);
    numTilesY.addListener(this, &ofApp::numTilesYChanged);
    
    gui.setup("controls");
    gui.add( colours.setup("colours", 0, 0, 255) );
    gui.add( scale.setup("scale", 1.0f, 1.0f, 0.001f) );
    gui.add( pos.setup("pos", 0, 0, 20) );
    gui.add( numTilesX.setup("cols", 16, 1, 24) );
    gui.add( numTilesY.setup("rows", 4, 1, 24) );
    gui.add( economics.updateThreshold.set(0.7f) );
    gui.add( animationDecay.setup("elasticity", 0.05, 0.0001, 0.2) );
    
    // start the animation values on the same values
    coloursAnimator = 0;
    scaleAnimator = 1.0f;
    posAnimator = 0;
    
    // setup tiles last
    isSetup = true;
    initTiles();
}

//--------------------------------------------------------------
void ofApp::exit()
{
	numTilesX.removeListener(this, &ofApp::numTilesXChanged);
    numTilesY.removeListener(this, &ofApp::numTilesYChanged);
    ofRemoveListener(economics.onEconomicRise, this, &ofApp::onEconomicRise);
    ofRemoveListener(economics.onEconomicFall, this, &ofApp::onEconomicFall);
}


//--------------------------------------------------------------
void ofApp::update()
{
    // update the video
    video.update();
    if(video.isFrameNew())
    {
        // copy the current pixels
        currentFrame.setFromPixels( video.getPixelsRef() );
        
        // loop through each tile in the grid and draw it
        for (int i = 0; i < tileArray.size(); i++)
        {
            tileArray[i].img.cropFrom(currentFrame, tileArray[i].sX, tileArray[i].sY, tileArray[i].sW*scaleAnimator, tileArray[i].sH*scaleAnimator);
        }
    }

    // update the numbers
    economics.update();
    
    // ease the animations, fade the animation values back down
    // so the end on the slider values
    coloursAnimator += (colours-coloursAnimator) * animationDecay;
    scaleAnimator += (scale-scaleAnimator) * animationDecay;
    posAnimator += (pos-posAnimator) * animationDecay;
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // center the video in the screen
    ofPushMatrix();
    ofTranslate((ofGetWidth() - videoWidth) / 2, (ofGetHeight() - videoHeight) / 2);
    
    if (isGlitch)
    {
        
        ofSetColor(255);
        currentFrame.draw(0, 0);
        
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        
        // draw the tiles
        ofSetColor(255);
        for (int i = 0; i < tileArray.size(); i++)
        {
            ofSetColor(255-ofRandom(0,coloursAnimator), 255-ofRandom(0,coloursAnimator), 255-ofRandom(0,coloursAnimator), 255-ofRandom(0,coloursAnimator));
            tileArray[i].img.draw(tileArray[i].dX+ofRandom(posAnimator), tileArray[i].dY+ofRandom(posAnimator), tileArray[i].dW, tileArray[i].dH);
        }
        
        ofDisableBlendMode();
    }
    else {
        // just draw original video without glitch affects
        currentFrame.draw(0, 0);
    }
    
    ofPopMatrix();
    
    if (!isFullscreen)
    {
        ofSetColor(255);
        
        //debugger
        string debugStr = "'f' = fullscreen";
        if (isGlitch) {
            debugStr += " | 'g' = turn glitch off";
        }
        else {
            debugStr +=  " | 'g' = turn glitch on";
        }
        debugStr += " | ' ' = toggle pause | " + ofToString(ofGetFrameRate(), 0) + "fps";
        ofDrawBitmapString(debugStr, 10, ofGetHeight()-10);
        
        economics.draw(10,ofGetHeight()-130);
        gui.draw();
    }
}


//--------------------------------------------------------------
void ofApp::onEconomicRise(float &difference)
{
    
    
}

//--------------------------------------------------------------
void ofApp::onEconomicFall(float &difference)
{
    // maps the 0.0-2.0 value to a colour range
    // most commons value range is:0.01-0.35 with perlin noise
//    coloursAnimator = ofMap(abs(difference), 0.01, 0.35, 1, 255, true);
    scaleAnimator = ofMap(abs(difference), 0.01, 0.35, scale.getMin(), scale.getMax());
//    posAnimator = ofMap(abs(difference), 0.01, 0.35, pos.getMin(), pos.getMax());
}


//--------------------------------------------------------------
void ofApp::numTilesXChanged(int &newNumX)
{
    // [TODO] this function is called twice????
    initTiles();
}


//--------------------------------------------------------------
void ofApp::numTilesYChanged(int &newNumY)
{
    initTiles();
}


//--------------------------------------------------------------
void ofApp::initTiles()
{
    if (isSetup) {
        cout << "initTiles" << endl;
        
        int numTiles = numTilesX * numTilesY;
        
        tileArray.clear();
        tileArray.assign(numTiles, Tile());
        
        for (int i = 0; i < numTiles; i++)
        {
            tileArray[i].setPos(i, numTiles, numTilesX, numTilesY, videoWidth, videoHeight, videoWidth, videoHeight);
        }
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
void ofApp::keyPressed(int key)
{
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

// attempt at accounting for placement of tiles in accordance with scale modifier
// tileArray[i].img.draw(tileArray[i].dX+ofRandom(posAnimator)-(scaleAnimator*tileArray[i].dX-tileArray[i].dX)/2, tileArray[i].dY+ofRandom(posAnimator)-(scaleAnimator*tileArray[i].dY-tileArray[i].dY)/2, tileArray[i].dW, tileArray[i].dH);

// path to my video
// /Users/peterhudson/Downloads/wetransfer-143c26/NewsFromSomewhereFourthEditWithCuts.mp4


//ofSetColor(255);
//for (int i = 0; i < numTiles; i++) {
//    ofDrawBitmapString( "i = " + ofToString(i) + "\t" + ofToString(tileArray[i].dX) + " dX\t" + ofToString(tileArray[i].dY)+ " dY\t" +ofToString(tileArray[i].dW)+ " dW\t" +ofToString(tileArray[i].dH)+ " dH\t", 20, 20 + (i*12));
//}


//ofSetColor(255);
//for (int i = 0; i < numTiles; i++) {
//    ofDrawBitmapString( "i = " + ofToString(i) + "\t" + ofToString(tileArray[i].dX) + " dX\t" + ofToString(tileArray[i].dY)+ " dY\t" +ofToString(tileArray[i].dW)+ " dW\t" +ofToString(tileArray[i].dH)+ " dH\t", 20, 20 + (i*12));
//}



