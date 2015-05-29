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

void ofApp::setupGUI()
{
    int n1 = sizeof(internalFormats) / sizeof(int);
    int n2 = sizeof(formats) / sizeof(int);
    
    gui.setup();
    gui.add(inner.setup("internal", 0, 0, n1-1));
    gui.add(pack.setup("format", 5, 0, n2-1));
    gui.add(widthPrc.setup("width", 1.0f, 0.95f, 1.0f));
    gui.add(heightPrc.setup("height", 1.0f, 0.0f, 1.0f));
}

void ofApp::togglePlay() {
	if (isPlaying) {
		pause();
	} else {
		play();
	}
}

void ofApp::pause() {
    isPlaying = false;
	media->pause();
}

void ofApp::play() {
    isPlaying = true;
	media->play();
}



//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowTitle("Destructive Destruction");
    ofSetVerticalSync(true);
	ofBackground(.15 * 255);
    
    setupGUI();
    
    isPlaying = true;

    media = new ofxTLVideoGlitch();
	media->load("/Users/lukesturgeon/Dropbox/4 - RCA/11 - Glitch Films/2 - Production/Assets/DestructiveDestructionSecondtEdit.mp4");
	media->play();
}

//--------------------------------------------------------------
void ofApp::update()
{
	media->update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    float innerFormat = internalFormats[ inner ];
	float packFormat = formats[ pack ];
	
	
	// set compression
	//ofTexCompression compression;
	//tex.setCompression(compression);
	
	media->draw(widthPrc, heightPrc, innerFormat, packFormat);
    
    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 20, ofGetHeight()-20);
	   
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 'f') {
		ofToggleFullscreen();
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
    media->load(file);
    
    cout << file << endl;
}
