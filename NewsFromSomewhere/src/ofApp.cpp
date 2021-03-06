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
    isFreeScale = false;
    isVideoFinished = true;
    
    // the global video width and height
    videoWidth.set(1280);
    videoHeight.set(720);
    
    // setup economics
    ofAddListener(economics.onEconomicRise, this, &ofApp::onEconomicRise);
    ofAddListener(economics.onEconomicFall, this, &ofApp::onEconomicFall);
    
    // setup video
    currentFrame.allocate(videoWidth, videoHeight, OF_IMAGE_COLOR);
    
    video.setPixelFormat(OF_PIXELS_RGBA);
    ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
    video.loadMovie("/Users/lukesturgeon/Dropbox/4 - RCA/11 - Glitch Films/2 - Production/Assets/NewsFromSomewhere.mp4", decodeMode);
    video.setLoopState(OF_LOOP_NORMAL );
    play();
    
    // setup GUI
    numTilesX.addListener(this, &ofApp::numTilesXChanged);
    numTilesY.addListener(this, &ofApp::numTilesYChanged);
    
    gui.setup("controls");
    gui.add( colours.setup("colours", 0, 0, 255) );
    gui.add( scale.setup("scale", 1.0f, 1.0f, 0.001f) );
    gui.add( pos.setup("pos", 0, 0, 20) );
    gui.add( numTilesX.setup("cols", 10, 1, 24) );
    gui.add( numTilesY.setup("rows", 8, 1, 24) );
    gui.add( animationDecay.setup("elasticity", 0.01, 0.0001, 0.2) );
    
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
        
        // clear data when video resets, to make data interesting
        if(video.getPosition() == 1.0 && !isVideoFinished){
            cout << "VIDEO END, RESET DATA" << endl;
            economics.resetHistory();
            isVideoFinished = true;
        }
        if (video.getPosition() > 0.0 && isVideoFinished) {
            cout << "VIDEO STARTING" << endl;
            isVideoFinished = false;
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
        ofScale(sw, sh);
    }
    
    if (isGlitch)
    {
        ofSetColor(255);
        currentFrame.draw(0, 0);
        
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        
        // draw the tiles
        ofSetColor(255);
        for (int i = 0; i < tileArray.size(); i++)
        {
            if(tileArray[i].img.bAllocated()) {
                ofSetColor(255-ofRandom(0,coloursAnimator), 255-ofRandom(0,coloursAnimator), 255-ofRandom(0,coloursAnimator), 255-ofRandom(0,coloursAnimator));
                tileArray[i].img.draw(tileArray[i].dX+ofRandom(posAnimator), tileArray[i].dY+ofRandom(posAnimator), tileArray[i].dW, tileArray[i].dH);
            }
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
            debugStr += " | 'g/[click]' = glitch off";
        }
        else {
            debugStr +=  " | 'g/[click]' = glitch on";
        }
        debugStr += " | ' ' = toggle pause";
        debugStr += " | 's' = toggle scale";
        debugStr += " | " + ofToString(ofGetFrameRate(), 0) + "fps";
        ofDrawBitmapString(debugStr, 10, ofGetHeight()-10);
        
        ofDrawBitmapStringHighlight("scaleAnimator: " + ofToString(scaleAnimator), 10, 500);
        
        gui.draw();
        
        economics.draw(10,ofGetHeight()-130);
    }
}


//--------------------------------------------------------------
void ofApp::onEconomicRise(float &difference)
{
    // maps the incoming number to an effect
    // 1 is the highest it could drop with the data provided
    // 0-0.99999 is a drop that's small than the max
    cout << "> rise with " << difference << endl;
    scaleAnimator = ofMap(abs(difference), 0.0f, 1.0f, scale.getMin(), scale.getMax());
    
}

//--------------------------------------------------------------
void ofApp::onEconomicFall(float &difference)
{
    // maps the incoming number to an effect
    // 1 is the highest it could drop with the data provided
    // 0-0.99999 is a drop that's small than the max
    cout << "> drop with " << difference << endl;
    scaleAnimator = ofMap(abs(difference), 0.0f, 1.0f, scale.getMin(), scale.getMax());
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
    if (isSetup)
    {
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
    if (key == 's')
    {
        // change the scale mode
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



