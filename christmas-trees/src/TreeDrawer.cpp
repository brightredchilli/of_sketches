//
//  TreeDrawer.cpp
//  christmas-trees
//
//  Created by Ying Quan Tan on 12/9/17.
//

#include "TreeDrawer.hpp"

using namespace ofxCv;
using namespace cv;

struct PolylineSortByArea {
    inline bool operator() (const ofPolyline& line1, const ofPolyline& line2) {
        return (line1.getArea() < line2.getArea());
    }
};

ofPath polylineToPath(const ofPolyline &polyline) {
    ofPath path;

    for (int i = 0; i < polyline.size(); i++) {
        auto vertex = polyline[i];
//        if (i == 0) {
//            path.moveTo(vertex);
//        } else {
//
//        }
        path.lineTo(vertex);
        if (polyline.isClosed()) {
            path.close();
        }
    }
    return path;
}

TreeDrawer::TreeDrawer(const std::string& filename,
                       ofRectangle bounds) : bounds(bounds) {

    ratio = 0.1; // default is 30% of width
    pathScale = 1.;
    image.load(filename);
    setupContours();

    // if we're drawing the original image, we should resize.
//    image.resize(image.getWidth()*.2, image.getHeight()*.2);

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


//    fbo.allocate(image.getWidth(), image.getHeight(), GL_LUMINANCE);
//    fbo.begin();
//    outline.draw();
//    fbo.end();
}

void TreeDrawer::setupContours() {
    
    contourFinder.setSortBySize(true);
    contourFinder.setMinAreaRadius(130);
    contourFinder.resetMaxArea();
    contourFinder.setFindHoles(true);
    contourFinder.setInvert(true);
    contourFinder.setThreshold(50);
    contourFinder.findContours(image);

    polylines = contourFinder.getPolylines();
    sort(polylines.begin(), polylines.end(), PolylineSortByArea());
    for (int i = 0; i < polylines.size(); i++) {
        auto line = polylines[i];
        line = line.getResampledBySpacing(130); // try to smooth a much smaller image
        ofLog() << "path size: " << line.size();
        ofPath path;
        for (int i = 0; i < line.size(); i++) {
            auto vertex = line[i];
            path.lineTo(vertex);
            if (i == line.size() - 1 && line.isClosed()) {
                path.close();
            }
        }
//        path.scale(pathScale, pathScale);
        paths.push_back(path);

    }

    // convert paths to meshes
    meshes.clear();

    // largest mesh should be first, we get it's centroid as that encompasses the entire image.
    auto centroid =  polylines[0].getCentroid2D();

    for (auto path : paths) {
        ofVboMesh mesh = path.getTessellation();

        vector<ofVec3f> &vertices = mesh.getVertices();
        for (int i = 0; i < vertices.size(); i++) {
            // center the vertex around 0 for easier scaling
            vertices[i] = (vertices[i] - centroid);
        }
        meshes.push_back(mesh);
    }

//    for (int i = 0; i < meshes.size(); i++) {
//        ofVboMesh &mesh = meshes[i];
//        auto centroid =  mesh.getCentroid();
//        for (int i = 0; i < mesh.getNumIndices(); i++) {
//            mesh.getVertices()[i] = mesh.getVertices()[i] - centroid;
//        }
//    }

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
//    image.draw(0, 0);


//    ofSetLineWidth(7);
    ofScale(1/pathScale, 1/pathScale); // recover the scale from the path

    for (int i = 0; i < paths.size(); i++) {
//        cout << i << endl;
        int offset = ofMap(fmod(ofGetElapsedTimef(), 1), 0,  1, 0, colors.size()-1);
        ofColor color = colors[(i + offset) % colors.size()];
        ofSetColor(color);
//
//        ofPath path = paths[i];
        ofVboMesh &mesh = meshes[i];
//        mesh.clearColors();
//        mesh.setColorForIndices(0, mesh.getNumIndices(), color);
        mesh.draw();

        
//        path.setFilled(true);
//        path.setFillColor(color);
//
//        // we scale so that this path will draw like RECTMODE_CENTER
//        path.scale(1/pathScale, 1/pathScale);
//        path.translate(ofPoint(-image.getWidth()/2, -image.getHeight()/2));
//        path.draw();
    }
    

    int imageWidth = image.getWidth();
    int imageHeight = image.getHeight();

    ofPopStyle();
    ofPopMatrix();
}

void TreeDrawer::setRandomSeed(int seed) {
    randomSeed = seed;
}

