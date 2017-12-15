#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    /// Setup panel and defaults
    panel.setup();
    //panel.add(parameter);
    panel.loadFromFile("settings.xml");
    bounds.set(0, 0, ofGetWidth(), ofGetHeight());
    center.set(bounds.getCenter());

    grabber.initGrabber(1280, 720);
    scale = 2;
    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update() {
    grabber.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
//    grabber.draw(0, 0);

    ofPushMatrix();
    ofScale(scale, scale);
    ofMesh myMesh;
    myMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

    float distance = 0;

    float time = ofGetElapsedTimef();

    int totalLength = line.getLengthAtIndex(-1);

    for (int i = 0; i < line.size(); i++){


        int i_m_1 = MAX(i-1,0);
        int i_p_1 = MIN(i+1,line.size()-1);
        ofPoint a = line[i_m_1];
        ofPoint b = line[i_p_1];

        distance += (line[i] - a).length();

        ofPoint diff = b-a;
        diff.normalize();
        diff.rotate(90, ofPoint(0,0,1));
        ofPoint up = line[i] + diff * 100;
        ofPoint down = line[i] - diff * 100;

        myMesh.addVertex(up);
        myMesh.addVertex(down);

        myMesh.addColor(ofColor::white);
//        myMesh.addColor(ofColor::white);

        float pct = ofMap(i, 0, line.size(), 0, 1);

        myMesh.addTexCoord(grabber.getTexture().getCoordFromPoint(up.x, up.y));
        myMesh.addTexCoord(grabber.getTexture().getCoordFromPoint(down.x, down.y));


        // This repeats the video stream, oscilatting from 0 to grabber.getWidth(), using abs
        // to 'reflect' when it gets to the end
        // float x = abs(grabber.getWidth() - fmod(distance, grabber.getWidth() * 2));

        // Adds an offset based on sin of time that adjusts the offset from beginning, making it
        // thing 'undulate'
//        float offset = ofMap(sin(time), -1, 1, 0, grabber.getWidth());
//        float x = abs(grabber.getWidth() - fmod(distance + offset, grabber.getWidth() * 2));

//        myMesh.addTexCoord(  grabber.getTexture().getCoordFromPoint(x, 0) );
//        myMesh.addTexCoord(  grabber.getTexture().getCoordFromPoint(x, grabber.getHeight())   );

//        myMesh.addVertex(line[i]);
        myMesh.addColor(ofColor(255,255,255,255*pct));
//        myMesh.addColor(ofColor(255,255,255*pct,255*pct));
    }
    grabber.getTexture().bind();

    myMesh.draw();
    grabber.getTexture().unbind();

    ofPopMatrix();

    panel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    line.clear();
}

void ofApp::mouseDragged(int x, int y, int button) {
    line.addVertex(x/scale,y/scale);
}

