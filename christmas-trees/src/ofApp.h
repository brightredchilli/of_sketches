#pragma once

#include "ofMain.h"
#import "ofxGui.h"
#include "ofxCv.h"
#include "TreeDrawer.hpp"

class ofApp : public ofBaseApp {

  public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void mouseMoved(int x, int y );
    void mousePressed(int x, int y, int button);

  protected:
    
    vector <ofColor> colors;
    ofPoint center;
    ofRectangle bounds;
    ofxPanel panel;

    /// Edge

    /// Contour
    ofParameter <float> threshold;

    ofFbo fboMask;
    ofFbo fbo;

    TreeDrawer *drawer;

    void drawTest();

};
