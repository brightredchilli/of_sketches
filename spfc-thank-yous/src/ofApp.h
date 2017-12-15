#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

    ofPoint center;
    ofFbo fbo;
    int baseColorHue;
    bool recording;
    float seed;
    void drawPolygon(ofPoint polygonCenter, float time, int baseHue);

    void mousePressed(int x, int y, int button);
    void mouseMoved(int x, int y);
    void keyPressed(int key);
};
