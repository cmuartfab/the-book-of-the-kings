#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    w = ofGetScreenWidth(); h = ofGetScreenHeight();
    ofSetWindowShape(w, h);
    ofSetFullscreen(true);
    
    compostW = 800; compostH = 600;
    compostPos = ofVec2f(w/2 - compostW/2, h/2 - compostH/2);
    
    m1.loadImage("1.png"); m2.loadImage("2.png");
    m3.loadImage("3.png"); m4.loadImage("4.png");
    
    camW = 640; camH = 480;
    cam.setDeviceID(0);
    cam.initGrabber(camW, camH);
    
    resultImage.allocate(camW, camH);
    
    artk.setup(camW, camH);
    threshold = 85;
    artk.setThreshold(threshold);
    
    ofSetLogLevel(OF_LOG_NOTICE);

    checkForNewImages();
}

//--------------------------------------------------------------
void ofApp::checkForNewImages() {
    dir.listDir("images");
    dir.sort();
    
    for(int i = 0; i < (int)dir.size(); i++) {
        string filename = dir.getPath(i);
        ofImage thisImg; thisImg.loadImage(filename);
        ofVec2f randPos = ofVec2f(ofRandom(compostW), ofRandom(compostH));
        
        while(randPos.x + thisImg.getWidth() > compostW ||
           randPos.y + thisImg.getHeight() > compostH) {
            thisImg.resize(thisImg.getWidth()/2, thisImg.getHeight()/2);
        }
        imagesPos.push_back(randPos);
        images.push_back(thisImg);
        
        char rm_command [strlen(filename.c_str()) + 10];
        std::sprintf(rm_command, "rm ../../../data/%s", filename.c_str());
        //std::system(rm_command);
    }
    if(images.size() > 0) framesLeftToShowImages = SHOW_IMAGES_FOR;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    cam.update();
    if(cam.isFrameNew()) {
        colorImage.setFromPixels(cam.getPixels(), camW, camH);
        grayImage = colorImage;
        
        //grayImage.mirror(false, true); //do this if using mirror
        grayImage.threshold(mouseX);
        artk.update(grayImage.getPixels());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //make sure to pop images after u draw them, then make sure to save compost periodically
    //don't update every frame
    
    ofBackground(255);
    
    //===========================================================
    // ARTK + COMPOST
    //===========================================================
    int numMarkers = artk.getNumDetectedMarkers();
    
    ofSetColor(255);
    grayImage.draw(0, 0, w, h);
    ofSetHexColor(0x666666);
    ofDrawBitmapString(ofToString(numMarkers) + " marker(s) found", 10, 20);
    artk.draw(0, 0, w, h);
    
    //===========================================================
    // MARKERS
    //===========================================================
    ofSetColor(255);
    ofFill();
    
    ofSetRectMode(OF_RECTMODE_CORNER);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

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
