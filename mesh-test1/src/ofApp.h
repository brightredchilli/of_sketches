#pragma once

#include "ofMain.h"
#import "ofxGui.h"

class ofApp : public ofBaseApp {

  public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void mouseMoved(int x, int y );
    void mousePressed(int x, int y, int button);

  protected:
    ofPoint center;
    ofRectangle bounds;
    ofxPanel panel;
    ofPolyline line;

    void drawPrimitiveTriangles();
    void drawPrimitiveTriangleStrip();
};
