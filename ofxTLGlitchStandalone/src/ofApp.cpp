#include "ofApp.h"

int internalFormats[] = {
    GL_RGB,
    GL_COMPRESSED_LUMINANCE,
    GL_COMPRESSED_LUMINANCE_ALPHA,
    GL_COMPRESSED_INTENSITY,
    GL_COMPRESSED_RGB,
    GL_COMPRESSED_RGBA,
    GL_DEPTH_COMPONENT,
    GL_DEPTH_COMPONENT16,
    GL_DEPTH_COMPONENT24,
    GL_DEPTH_COMPONENT32,
    GL_LUMINANCE,
    GL_INTENSITY,
    GL_INTENSITY4,
    GL_INTENSITY8,
    GL_INTENSITY12,
    GL_INTENSITY16,
    GL_R3_G3_B2,
    GL_SLUMINANCE,
    GL_SLUMINANCE8,
    GL_SLUMINANCE_ALPHA,
    GL_SLUMINANCE8_ALPHA8,
    GL_SRGB, GL_SRGB8,
    GL_SRGB_ALPHA,
    GL_SRGB8_ALPHA8
};

int formats[] = {
    GL_COLOR_INDEX,
    GL_RED,
    GL_GREEN,
    GL_BLUE,
    GL_ALPHA,
    GL_RGB,
    GL_BGR,
    GL_RGBA,
    GL_BGRA,
    GL_LUMINANCE,
    GL_LUMINANCE_ALPHA
};

void ofApp::togglePlay() {
	if (isPlaying) {
		pause();
	} else {
		play();
	}
}

void ofApp::pause() {
    isPlaying = false;
    media.setPaused(!isPlaying);
}

void ofApp::play() {
    isPlaying = true;
	media.setPaused(!isPlaying);
}



//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowTitle("Destructive Destruction");
    ofSetVerticalSync(true);
	ofBackground(.15 * 255);
    isFullscreen = false;
    
    // setup the economics numbers
    
    // Setup the GUI
    int n1 = sizeof(internalFormats) / sizeof(int);
    int n2 = sizeof(formats) / sizeof(int);
    
    mediaSettingsA.setName( "VIDEO A");
    mediaSettingsA.add( innerA.set("internal", 0, 0, n1-1));
    mediaSettingsA.add( packA.set("format", 5, 0, n2-1));
    mediaSettingsA.add( widthPrcA.set("width", 1.0f, 0.95f, 1.0f));
    mediaSettingsA.add( heightPrcA.set("height", 1.0f, 0.0f, 1.0f));
    mediaSettingsA.add( tintA.set("tint", ofColor(255, 127), ofColor(0,0), ofColor(255)) );
    
    mediaSettingsB.setName( "VIDEO B");
    mediaSettingsB.add( innerB.set("internal", 0, 0, n1-1));
    mediaSettingsB.add( packB.set("format", 5, 0, n2-1));
    mediaSettingsB.add( widthPrcB.set("width", 1.0f, 0.95f, 1.0f));
    mediaSettingsB.add( heightPrcB.set("height", 1.0f, 0.0f, 1.0f));
    mediaSettingsB.add( tintB.set("tint", ofColor(255), ofColor(0,0), ofColor(255)) );
    
    gui.setup();
    gui.add(mediaSettingsA);
    gui.add(mediaSettingsB);
    
    // Load the video file
   	media.loadMovie("/Users/lukesturgeon/Dropbox/4 - RCA/11 - Glitch Films/2 - Production/Assets/DestructiveDestructionFourthEdit.mp4");
	play();
}

//--------------------------------------------------------------
void ofApp::update()
{
    economics.update();
	media.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // draw the original video B
    ofSetColor( tintB );
    drawGlitchedVideo(media, widthPrcB, heightPrcB, internalFormats[ innerB ], formats[ packB ]);
    
    // draw the glitched video A
    ofSetColor( tintA );
    drawGlitchedVideo(media, widthPrcA, heightPrcA, internalFormats[ innerA ], formats[ packA ]);
    
    if( !isFullscreen ) {
        ofSetColor(255);
        ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 20, ofGetHeight()-20);
        
        gui.draw();
        economics.draw(20, 500);
    }
}

//--------------------------------------------------------------
void ofApp::drawGlitchedVideo(ofVideoPlayer & video, float width, float height, float innerFormat, float packFormat)
{
    ofTexture tex;
    tex.allocate(video.width, video.height, innerFormat);
    tex.loadData(video.getPixels(), video.width * width, video.height * height, packFormat);
    tex.draw( (ofGetWidth() - video.width) / 2, (ofGetHeight() - video.height) / 2, video.width, video.height);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 'f') {
        isFullscreen = !isFullscreen;
        ofSetFullscreen(isFullscreen);
	}
    if(key == ' ') {
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
    media.loadMovie(file);
    
    cout << file << endl;
}
