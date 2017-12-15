//
//  TreeDrawer.cpp
//  christmas-trees
//
//  Created by Ying Quan Tan on 12/9/17.
//

#include "TreeDrawer.hpp"

using namespace ofxCv;
using namespace cv;

TreeDrawer::TreeDrawer(const std::string& filename,
                       ofRectangle bounds) : bounds(bounds) {

    ratio = 0.3; // default is 30% of width

    image.load(filename);
    // original image is 1400px!:D
    image.resize(image.getWidth()*.2, image.getHeight()*.2);

    ofImage dot("Snowflake-01.png");
    ornaments.push_back(dot);

    randomSeed = ofRandom(INT_MAX);

    colors.push_back(ofColor(116, 0 , 191));
    colors.push_back(ofColor(204, 10, 143));
    colors.push_back(ofColor(206, 11, 214));
    colors.push_back(ofColor(90, 11, 214));
    colors.push_back(ofColor(45, 10, 204));
    colors.push_back(ofColor(230, 12, 99));
    colors.push_back(ofColor(230, 133, 23));
    colors.push_back(ofColor(199, 230, 23));
    colors.push_back(ofColor(12, 230, 170));

    setupContours();
    fbo.allocate(image.getWidth(), image.getHeight(), GL_LUMINANCE);
    fbo.begin();
    outline.draw();
    fbo.end();
}

void TreeDrawer::setupContours() {
    
    //    contourFinder.setSortBySize(true);
    contourFinder.setMinAreaRadius(100);
    contourFinder.resetMaxArea();
    contourFinder.setFindHoles(true);
    contourFinder.setInvert(true);
    contourFinder.setThreshold(250);
//    contourFinder.setThreshold(93);
    contourFinder.findContours(image);

    outline = contourFinder.getPolyline(0);
}

float TreeDrawer::getRatio() {
    return ratio;
}
void TreeDrawer::setRatio(float r) {
    ratio = r;
}

void TreeDrawer::setThreshold(float t) {
    contourFinder.setThreshold(t);
}

void TreeDrawer::update() {

}


void TreeDrawer::draw(int x, int y) {

//    ofSeedRandom(randomSeed);

    float drawRatio = bounds.getWidth() / image.getWidth() * ratio;
    ofPushMatrix();
    ofPushStyle();

    ofSetRectMode(OF_RECTMODE_CENTER);
    ofTranslate(x, y);
    ofScale(drawRatio, drawRatio);
    image.draw(0, 0);

//    ofPushMatrix();
//    ofPushStyle();
//    ofSetLineWidth(7);
//    for (int i = 0; i < contourFinder.size()-1; i++) {
//        cout << i << endl;
//        int offset = ofMap(fmod(ofGetElapsedTimef(), 1), 0, 1, 0, colors.size()-1);
//        ofColor color = colors[(i + offset) % colors.size()];
//
//        ofPolyline line = contourFinder.getPolyline(i);
//        ofPath path;
//        for (int i = 0 ; i < line.size(); i++) {
//            path.lineTo(line[i]);
//        }
//        path.close();
//        path.setFilled(true);
//        path.setFillColor(color);
//        path.translate(ofPoint(-image.getWidth()/2, -image.getHeight()/2));
//        path.draw();
//    }
//    ofPopStyle();
//    ofPopMatrix();

    int imageWidth = image.getWidth();
    int imageHeight = image.getHeight();

//    int numOrnaments = ofRandom(5, 20);
//    int cnt = 0;
//    while (cnt < numOrnaments) {
//        int x = ofRandom(0, imageWidth);
//        int y = ofRandom(0, imageHeight);
//        if (outline.inside(x, y)) {
//            int idx = ofRandom(0, ornaments.size());
//            ofPushMatrix();
//            ofTranslate(x - imageWidth/2, y - imageHeight/2);
//            if (ofRandomf() < 0.5) {
//                ofScale(0.65, 0.65);
//            }
//            ornaments[idx].draw(0, 0);
//            ofPopMatrix();
//            cnt++;
//        }
//    }

    ofPopStyle();
    ofPopMatrix();
}

void TreeDrawer::setRandomSeed(int seed) {
    randomSeed = seed;
}

