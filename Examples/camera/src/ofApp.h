#pragma once

#include "ofMain.h"
#include "ofxOpenCvTracker.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseDragged(int x, int y, int button);

    ofVideoGrabber camera;
    vector<ofxOpenCvTracker> tracker;
    ofRectangle r;
};
