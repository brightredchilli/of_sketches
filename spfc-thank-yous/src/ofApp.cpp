#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    center.set(ofGetWidth()/2, ofGetHeight()/2);
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    seed = ofGetElapsedTimef();
//    fbo.allocate(1024*2, 768*2, GL_RGB);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
//    fbo.begin();
    ofSeedRandom(seed);
    ofSetLineWidth(0.1);
    ofBackground(255);
    ofSetColor(255);

    // split the rectangle up into 4 quadrants
    int paddingW = 60;
    int paddingH = 90;
    int row = 2;
    int col = 2;
    int boxHeight = (ofGetHeight() - paddingH*(row + 1)) / row;
    int boxWidth = (ofGetWidth() - paddingW*(col + 1)) / col;


    int count = 0;
    for (int y = paddingH; y < ofGetHeight(); y += boxHeight + paddingH) {
        for (int x = paddingW; x < ofGetWidth(); x += boxWidth + paddingW) {

            // draw a bounding box
            ofSetColor(200);
            ofNoFill();
            ofRectangle rect(x, y, boxWidth, boxHeight);
            ofDrawRectangle(rect);

            int hue = (baseColorHue + count*30) % 256;
            for (int i = 0; i < 40; i++) {
                drawPolygon(rect.getCenter(), 0.1 * i, hue);
            }
            count++;

        }
    }


    // draw bounding boxes

    if (recording) {
        ofImage img = ofImage();
        img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        img.save("screenshot " + ofGetTimestampString() + ".png");
        recording = false;
    }
//    fbo.end();
//    fbo.draw(ofPoint(0, 0));

}

void ofApp::drawPolygon(ofPoint polygonCenter, float time, int baseHue) {

    float slider1 = ofMap(ofGetMouseX(), 0, ofGetWidth(), 20, 100);
    float slider2 = ofMap(ofGetMouseY(), 0, ofGetHeight(), 4, 10);


    int numSides = 8;
    float degIncrement = TWO_PI / numSides;
    float startOffset = ofRandomf() * TWO_PI;


    ofPushMatrix();
    ofTranslate(polygonCenter);


    ofPolyline line;

    for (int i = 0; i < numSides; i++) {


        float noise = ofSignedNoise(i * 0.3 + seed + time);
        int hue = (int)(baseHue + 30 * noise) % 256;

        ofSetColor(ofColor::fromHsb(hue, ofRandom(180, 255), 255));

        float radius = 110 + 90 * ofRandomf();

        float angle = startOffset + degIncrement * i;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        x += ofNoise(x, time) * 20;
        y += ofNoise(y, time) * 20;

        line.addVertex(ofPoint(x, y));
    }
    line.close();
    line.draw();

    ofPopMatrix();
}

void ofApp::mousePressed(int x, int y, int button) {
    ofPoint direction = ofPoint(x, y) - center;
    float angleRad = atan2(direction.x, direction.y);
    baseColorHue = ofMap(angleRad, -PI, PI, 0, 255);

    seed = ofGetElapsedTimef();

}

void ofApp::mouseMoved(int x, int y) {
    ofPoint direction = ofPoint(x, y) - center;
    float angleRad = atan2(direction.x, direction.y);
    baseColorHue = ofMap(angleRad, -PI, PI, 0, 255);

    seed = ofGetElapsedTimef();

}

void ofApp::keyPressed(int key){
    if (key == 'x') {
        recording = !recording;
    }
}
