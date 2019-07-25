#include "ofxOpenCvTracker.h"

ofxOpenCvTracker::ofxOpenCvTracker()
{
    
}

ofxOpenCvTracker::~ofxOpenCvTracker()
{
    
}

void ofxOpenCvTracker::setup()
{
    is_found = false;
    setup("KCF"); // defalut
}
void ofxOpenCvTracker::setup(string _tracker_name)
{
    // tracker_algorithm can be:
    // MIL, BOOSTING, MEDIANFLOW, TLD, KCF, GOTURN, MOSSE
    tracker_name = _tracker_name;
}

void ofxOpenCvTracker::update(ofPixels &_p)
{
    if( tracker ){
        is_found = tracker->update(toCV(_p), bb);
    }
}


bool ofxOpenCvTracker::getFound()
{
    return is_found;
}

cv::Mat ofxOpenCvTracker::toCV(ofPixels &pix)
{
    return cv::Mat(pix.getHeight(), pix.getWidth(), CV_MAKETYPE(CV_8U, pix.getNumChannels()), pix.getData(), 0);
}

ofRectangle ofxOpenCvTracker::getTrackerRectangle()
{
    ofRectangle r_tracker;
    r_tracker.set(bb.x, bb.y, bb.width, bb.height);
    return r_tracker;
}
void ofxOpenCvTracker::set(ofPixels &_p, ofRectangle _r)
{
    _r.standardize();
    bb.width = _r.width;
    bb.height = _r.height;
    bb.x = _r.x;
    bb.y = _r.y;

    tracker = createTrackerByName(tracker_name);

    tracker->init(toCV(_p), bb);
    is_found = tracker->update(toCV(_p), bb);
}
