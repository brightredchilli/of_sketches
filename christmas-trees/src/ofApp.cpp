#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup() {
    /// Setup panel and defaults
    panel.setup();
    //panel.add(parameter);
    panel.add(threshold.set("threshold", 128, 0, 255));
    panel.loadFromFile("settings.xml");
    bounds.set(0, 0, ofGetWidth(), ofGetHeight());
    center.set(bounds.getCenter());

//    fbo.allocate(tree.getWidth()*1.1, tree.getHeight()*1.1);

    drawer = new TreeDrawer("Tree_b_tr-01.png", bounds);
}

//--------------------------------------------------------------
void ofApp::update() {
    drawer->update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(255);

//    fbo.begin();
//    fbo.getTexture().setAlphaMask(<#ofTexture &mask#>)

    ofSeedRandom(0);

    float time = ofGetElapsedTimef();
    for (int x = 0; x < bounds.width; x += 100) {
        for (int y = 50; y < bounds.height; y += 100) {
            float r = ofMap(sin(ofGetElapsedTimef() * 0.8), -1, 1, 0.005, 0.1);
            float jump = ofNoise(x, y, time);
            float offset = ofMap(jump, 0, 1, -10, 50);
            drawer->setRatio(r);
            drawer->draw(x, y + offset);
        }
    }


//    drawer->setRatio(0.5);
//    drawer->draw(center.x, center.y);


    ofPushMatrix();
    ofPushStyle();
    ofSetLineWidth(3);

    ofSetColor(255, 0, 0);
//    gray.draw(0, 0);

//    edge.draw(640, 0);
//    ofSetColor(0, 255, 0);
//    sobel.draw(640, 480);

    /// Contour code
//    contourFinder.draw();
//    for (int i = 0; i < contourFinder.size(); i++) {
//        ofSetColor(i * 60 % 255, (100 + i * 60) % 255, (150 + i * 60) % 255);
//        ofPolyline line = contourFinder.getPolyline(i);
//        line.draw();
//    }

//    if (contourFinder.size() > 0) {
//        if (contourFinder.size() > 1) {
//            cout << "WARNING: Found more than one contour" << endl;
//        }
//        ofSetColor(255, 0, 0);
//        int i = ofMap(mouseY, 0, ofGetHeight(), 0, contourFinder.size() - 1);
//        ofPolyline line = contourFinder.getPolyline(i);
//        line.draw();
//    }


    ofPopStyle();
    ofPopMatrix();
    panel.draw();




    char buff[5];
    snprintf(buff, 5, "%.2f", ofGetFrameRate());
    ofDrawBitmapStringHighlight(buff, bounds.width - 33, 12);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    threshold = ofMap(x, 0, ofGetWidth(), 0, 255);
//    drawer->setThreshold(threshold);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    drawer->setRandomSeed(ofRandom(0, INT_MAX));
}

