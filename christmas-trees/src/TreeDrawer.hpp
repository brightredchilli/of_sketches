//
//  TreeDrawer.hpp
//  christmas-trees
//
//  Created by Ying Quan Tan on 12/9/17.
//

#ifndef TreeDrawer_hpp
#define TreeDrawer_hpp

#include <stdio.h>
#include <string>
#include "ofMain.h"
#include "ofxCv.h"

class TreeDrawer {

public:
    TreeDrawer(const std::string& filename,
               ofRectangle bounds);
    ofImage image;

    float getRatio();

    // Ratio between the screen width and the image width
    void setRatio(float r);
    void setThreshold(float t);


    void setRandomSeed(int seed);
    void draw(int x, int y);
    void update();

    vector <ofVboMesh> meshes;

protected:

    vector <ofColor> colors;
    ofFbo fbo;
    ofxCv::ContourFinder contourFinder;
    ofRectangle bounds;

    vector <ofImage> ornaments;
    float ratio;
    float pathScale;
    int randomSeed;
    vector <ofPath> paths;

    vector <ofPolyline> polylines;

    void setupContours();

};

#endif /* TreeDrawer_hpp */
