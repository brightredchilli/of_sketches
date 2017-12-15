#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    /// Setup panel and defaults
    panel.setup();
    //panel.add(parameter);
    panel.loadFromFile("settings.xml");
    bounds.set(0, 0, ofGetWidth(), ofGetHeight());
    center.set(bounds.getCenter());
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
    drawPrimitiveTriangleStrip();

    panel.draw();
}

void ofApp::drawPrimitiveTriangleStrip() {
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    for (int i = 0; i < line.size(); i++) {
        mesh.addVertex(line[i]);

        int colorIdx = i % 3;
        ofFloatColor color;
        switch (colorIdx) {
            case 0:
                color.set(1, 0, 0);
                break;
            case 1:
                color.set(0, 1, 0);
                break;
            case 2:
                color.set(0, 0, 1);
                break;
        }

        mesh.addColor(color);

    }

    mesh.draw();
    mesh.drawWireframe();
}


void ofApp::drawPrimitiveTriangles() {
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    for (int i = 0; i < line.size(); i++) {
        mesh.addVertex(line[i]);

        int colorIdx = i % 3;
        ofFloatColor color;
        switch (colorIdx) {
            case 0:
                color.set(1, 0, 0);
                break;
            case 1:
                color.set(0, 1, 0);
                break;
            case 2:
                color.set(0, 0, 1);
                break;
        }

        mesh.addColor(color);

    }
    mesh.draw();
    mesh.drawWireframe();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

    if (button == 0) {
        line.addVertex(x, y);
    } else if (button == 2) {
        line.clear();
    }
}

