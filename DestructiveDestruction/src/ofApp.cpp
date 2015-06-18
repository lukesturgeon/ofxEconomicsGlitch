#include "ofApp.h"


int internalFormats[] = {
    GL_RGB,
//    GL_COMPRESSED_LUMINANCE,
    GL_DEPTH_COMPONENT16,
//    GL_COMPRESSED_LUMINANCE_ALPHA,
//    GL_COMPRESSED_INTENSITY,
//    GL_COMPRESSED_RGB,
//    GL_COMPRESSED_RGBA,
    GL_LUMINANCE,
//    GL_INTENSITY,
//    GL_INTENSITY4,
//    GL_INTENSITY8,
//    GL_INTENSITY12,
//    GL_INTENSITY16,
//    GL_R3_G3_B2,
//    GL_SLUMINANCE,
//    GL_SLUMINANCE8,
//    GL_SLUMINANCE_ALPHA,
//    GL_SLUMINANCE8_ALPHA8,
//    GL_SRGB,
//    GL_SRGB8,
//    GL_SRGB_ALPHA,
//    GL_SRGB8_ALPHA8,
    GL_DEPTH_COMPONENT,
    GL_DEPTH_COMPONENT24,
    GL_DEPTH_COMPONENT32
};

int formats[] = {
    GL_RGB,
    GL_COLOR_INDEX,
//    GL_RED,
//    GL_GREEN,
//    GL_BLUE,
    GL_ALPHA,
    
    GL_BGR,
//    GL_RGBA,
//    GL_BGRA,
    GL_LUMINANCE,
    GL_LUMINANCE_ALPHA
};



//--------------------------------------------------------------
void ofApp::setup()
{
//    ofSetDataPathRoot("../Resources/data/");
    
    ofSetWindowTitle("Destructive Destruction");
    ofSetVerticalSync(true);
	ofBackground(0);
    
    isPlaying = false;
    isFullscreen = false;
    isGlitch = true;
    isFreeScale = false;
    isVideoFinished = true;
    
    // the global video width and height
    videoWidth.set(1280);
    videoHeight.set(720);
    
    // setup the economics numbers
    ofAddListener(economics.onEconomicFall, this, &ofApp::onEconomicFall);
    
    // Setup the GUI
    int n1 = sizeof(internalFormats) / sizeof(int);
    int n2 = sizeof(formats) / sizeof(int);
    
    gui.setup();
    gui.add( innerA.set("internal", 0, 0, n1-1));
    gui.add( packA.set("format", 0, 0, n2-1));
    gui.add( widthPrcA.set("width", 1.0f, 0.95f, 1.0f));
    gui.add( heightPrcA.set("height", 1.0f, 0.0f, 1.0f));
    gui.add( tintA.set("tint", ofColor(255), ofColor(0,0), ofColor(255)) );

    gui.add( innerB.set("internal", 0, 0, n1-1));
    gui.add( packB.set("format", 0, 0, n2-1));
    gui.add( widthPrcB.set("width", 1.0f, 0.95f, 1.0f));
    gui.add( heightPrcB.set("height", 1.0f, 0.0f, 1.0f));
    gui.add( tintB.set("tint", ofColor(255), ofColor(0,0), ofColor(255)) );
    
    gui.add( animationDecay.setup("Elasticity", 0.005f, 0.0001f, 0.1f) );
    // Load the video file
   	video.loadMovie("/Users/lukesturgeon/Dropbox/4 - RCA/11 - Glitch Films/2 - Production/Assets/DestructiveDestruction.mp4");
    video.setLoopState( OF_LOOP_NORMAL );
	play();
}

//--------------------------------------------------------------
void ofApp::exit()
{
    ofRemoveListener(economics.onEconomicFall, this, &ofApp::onEconomicFall);
}

//--------------------------------------------------------------
void ofApp::update()
{
    economics.update();
	video.update();
    
    if(video.isFrameNew()){
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
    
    // ease back the animations
    if (innerAnimatorA > 0.1){
        innerAnimatorA += (innerA-innerAnimatorA) * animationDecay;
    }
    if (packAnimatorB > 0.1){
        packAnimatorB += (packB-packAnimatorB) * animationDecay;
//        cout << packAnimatorB << endl;
    }
    
    heightBAnimator += (heightPrcB-heightBAnimator) * animationDecay;
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    
    if (isGlitch){
        // draw the glitched video B
        ofSetColor( tintB );
//        drawGlitchedVideo(video, widthPrcB, heightBAnimator, internalFormats[ innerA ], formats[ packB ]);
        drawGlitchedVideo(video, widthPrcB, heightPrcB, internalFormats[ int(innerAnimatorA) ], formats[ int(packAnimatorB) ]);
        
        // draw the glitched video A
        ofEnableBlendMode(OF_BLENDMODE_SCREEN);
        ofSetColor( tintA );
        drawGlitchedVideo(video, widthPrcA, heightPrcA, internalFormats[ int(innerAnimatorA) ], formats[ packA ]);
        ofDisableBlendMode();
    }
    else {
        // just draw the original
        ofSetColor(255);
        drawGlitchedVideo(video, 1.0, 1.0, GL_RGB, GL_RGB);
    }
    
    if( !isFullscreen ) {
        ofSetColor(255);
        //debugger
        string debugStr = "'f' = fullscreen";
        if (isGlitch) {
            debugStr += " | 'g'/[click] = glitch off";
        }
        else {
            debugStr +=  " | 'g'/[click] = glitch on";
        }
        debugStr += " | ' ' = toggle pause";
        debugStr += " | 's' = toggle scale";
        debugStr += " | " + ofToString(ofGetFrameRate(), 0) + "fps";
        ofDrawBitmapString(debugStr, 10, ofGetHeight()-10);
        
        economics.draw(10,ofGetHeight()-130);
        
        ofDrawBitmapStringHighlight("innerAnimatorA: " + ofToString(innerAnimatorA), 10, 500);
        ofDrawBitmapStringHighlight("packAnimatorB: " + ofToString(packAnimatorB), 10, 530);
        ofDrawBitmapStringHighlight("heightBAnimator: " + ofToString(heightBAnimator), 10, 560);
        
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::togglePlay() {
	if (isPlaying) {
		pause();
	} else {
		play();
	}
}

//--------------------------------------------------------------
void ofApp::pause() {
    isPlaying = false;
    video.setPaused(!isPlaying);
}

//--------------------------------------------------------------
void ofApp::play() {
    isPlaying = true;
	video.setPaused(!isPlaying);
}

//--------------------------------------------------------------
void ofApp::drawGlitchedVideo(ofVideoPlayer & video, float width, float height, float innerFormat, float packFormat)
{
    ofTexture tex;
    
    try
    {
        tex.allocate(videoWidth, videoHeight, innerFormat);
        tex.loadData(video.getPixels(), videoWidth * width, videoHeight * height, packFormat);
    }
    catch (exception& e)
    {
        cout << "An exception occurred. Exception Nr. " << '\n';
    }
    
    if (isFreeScale)
    {
        // dont constran proportions, just fill the screen
        tex.draw( 0, 0, ofGetWidth(), ofGetHeight());
    }
    else
    {
        // keep the video at original width and height
        tex.draw( (ofGetWidth() - videoWidth) / 2, (ofGetHeight() - videoHeight) / 2, videoWidth, videoHeight);
    }
    
}

//--------------------------------------------------------------
void ofApp::onEconomicFall(float &difference)
{
    // maps the incoming number to an effect
    // 1 is the highest it could drop with the data provided
    // 0-0.99999 is a drop that's small than the max
    cout << "drop with " << difference << endl;
    innerAnimatorA = ofMap(abs(difference), 0.0f, 1.0f, innerA.getMin(), innerA.getMax());
    packAnimatorB = ofMap(abs(difference), 0.0f, 1.0f, packB.getMin(), packB.getMax());
    heightBAnimator = ofMap(abs(difference), 0.0f, 1.0f, heightPrcB.getMax(), heightPrcB.getMin());
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
        // toggle glitch
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
    
    cout << file << endl;
}
