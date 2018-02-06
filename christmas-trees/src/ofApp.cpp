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

    fbo.allocate(bounds.width, bounds.height);

    drawer = new TreeDrawer("Tree_b_tr-01.png", bounds);

    colors.push_back(ofColor(116, 0 , 191));
    colors.push_back(ofColor(204, 10, 143));
    colors.push_back(ofColor(206, 11, 214));
    colors.push_back(ofColor(90, 11, 214));
    colors.push_back(ofColor(45, 10, 204));
    colors.push_back(ofColor(230, 12, 99));
    colors.push_back(ofColor(230, 133, 23));
    colors.push_back(ofColor(199, 230, 23));
    colors.push_back(ofColor(12, 230, 170));
}

//--------------------------------------------------------------
void ofApp::update() {
    drawer->update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(255);


    ofSeedRandom(0);
//    ofVboMesh mesh;
//    vector<ofVboMesh> treeMeshes = drawer->meshes;
    int cnt = 0;
    float time = ofGetElapsedTimef();
    for (int x = 50; x < bounds.width; x += 20) {
        for (int y = 50; y < bounds.height; y += 20) {
//            float r = 0.05;
            float r = ofMap(sin(ofGetElapsedTimef() * 0.8), -1, 1, 0.005, 0.1);
            float jump = ofNoise(x, y, time);
            float offset = ofMap(jump, 0, 1, -10, 50);
            drawer->setRatio(0.01);
            drawer->draw(x, y + offset);

//            float treeX = x;
//            float treeY = y + offset;
//
//            for (int i = 0; i < treeMeshes.size(); i++) {
//                int offset = ofMap(fmod(ofGetElapsedTimef(), 1), 0, 1, 0, colors.size()-1);
//                offset += ofMap(ofNoise(x, y, time*0.2), 0, 1, 0, 4);
//                ofColor color = colors[(i + offset) % colors.size()];
//
//                ofMesh meshPart = treeMeshes[i]; // make a copy here
//                for (ofVec3f &vec : meshPart.getVertices()) {
////                    float scale = bounds.getWidth() / drawer->image.getWidth() * r;
//                    float scale = r * 0.1 + 0.05;
//                    vec *= scale * 0.3;
//                    vec += ofVec3f(treeX, treeY);
//                }
//                meshPart.setColorForIndices(0, meshPart.getNumIndices(), color);
//                mesh.append(meshPart);
//            }
//

        }
    }
//    mesh.draw();




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
    drawer->setThreshold(threshold);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    drawer->setRandomSeed(ofRandom(0, INT_MAX));
}

void ofApp::drawTest() {
    ofPushMatrix();
    ofPushStyle();

    float mult = sin(ofGetElapsedTimef() * 1.5) * 30 + 30;

    // First way
    //    for (int x = 0; x < bounds.width; x += 20) {
    //        for (int y = 50; y < bounds.height; y += 20) {
    //            ofSetColor(255, 0, 0);
    //            ofDrawRectangle(x, y, 10+mult, 10+mult);
    //        }
    //    }

    // Second Way
    //    ofVboMesh mesh;
    //    for (int x = 0; x < bounds.width; x += 20) {
    //        for (int y = 50; y < bounds.height; y += 20) {
    //            ofPath path;
    //            path.rectangle(x, y, 10 + mult, 10 + mult);
    //            mesh.append(path.getTessellation());
    //        }
    //    }
    //    mesh.setColorForIndices(0, mesh.getNumIndices(), ofColor(255, 0, 0));
    //    mesh.draw();

    //    ofPath path;
    //    path.rectangle(0, 0, 10 + mult, 10 + mult);
    //    ofMesh t = path.getTessellation();
    //
    //    auto centroid =  t.getCentroid();
    //    vector<ofVec3f> &vertices = t.getVertices();
    //    for (int i = 0; i < vertices.size(); i++) {
    //        // center the vertex around 0 for easier scaling
    //        vertices[i] = vertices[i] - centroid;
    //    }

    //    ofVboMesh mesh;
    //    for (int x = 50; x < bounds.width - 50; x += 20) {
    //        for (int y = 50; y < bounds.height - 50; y += 20) {
    //            ofMesh n = t; // copied!
    //            for (ofVec3f &vec : n.getVertices()) {
    //                vec += ofVec3f(x, y);
    //            }
    //            mesh.append(n);
    //        }
    //    }
    //    mesh.setColorForIndices(0, mesh.getNumIndices(), ofColor(255, 0, 0));
    //    mesh.draw();

    //    drawer->setRatio(0.5);
    //    drawer->draw(0, 0);


    ofPopStyle();
    ofPopMatrix();
}

