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
        tracker_image_width = image_width = _p.getWidth();
        tracker_image_height = image_height = _p.getHeight();
        
    }

}
void ofxOpenCvTracker::update(ofPixels &_p, int _tracker_image_width, int _tracker_image_height)
{
    if( tracker ){
        ofImage img;
        image_width = _p.getWidth();
        image_height = _p.getHeight();
        img.setFromPixels(_p);
        img.resize(_tracker_image_width, _tracker_image_height);
        is_found = tracker->update(toCV(img.getPixels()), bb);
        tracker_image_width = _tracker_image_width;
        tracker_image_height = _tracker_image_height;
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
    if(image_width == tracker_image_width &&
       image_height == tracker_image_height ){
        r_tracker.set(bb.x, bb.y, bb.width, bb.height);
    }
    else{
        float rate_x = image_width/(float)tracker_image_width;
        float rate_y = image_height/(float)tracker_image_height;
        r_tracker.set(bb.x*rate_x, bb.y*rate_y, bb.width*rate_x, bb.height*rate_y);
    }
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
    name = "undefined";
}

void ofxOpenCvTracker::setRectangle(ofRectangle _r, ofPixels &_p){
    bb.width = _r.width;
    bb.height = _r.height;
    bb.x = _r.x;
    bb.y = _r.y;
    tracker.reset();
    tracker.release();
    tracker = createTrackerByName(tracker_name);
    tracker->init(toCV(_p), bb);
    tracker->update(toCV(_p), bb);
}

void ofxOpenCvTracker::setName(string _name)
{
    name = _name;
}

void ofxOpenCvTracker::set(ofPixels &_p, ofRectangle _r,
                           int _tracker_image_width, int _tracker_image_height)
{
    image_width = _p.getWidth();
    image_height = _p.getHeight();
    tracker_image_width = _tracker_image_width;
    tracker_image_height = _tracker_image_height;
    
    _r.standardize();
    if(image_width == tracker_image_width &&
       image_height == tracker_image_height ){
        bb.width = _r.width;
        bb.height = _r.height;
        bb.x = _r.x;
        bb.y = _r.y;
    }
    else{
        float rate_x = tracker_image_width/(float)image_width;
        float rate_y = tracker_image_height/(float)image_height;
        bb.width = _r.width*rate_x;
        bb.height = _r.height*rate_y;
        bb.x = _r.x*rate_x;
        bb.y = _r.y*rate_y;
    }
    
    tracker = createTrackerByName(tracker_name);
    
    ofImage img;
    img.setFromPixels(_p);
    img.resize(_tracker_image_width, _tracker_image_height);
    tracker->init(toCV(img.getPixels()), bb);
    is_found = tracker->update(toCV(img.getPixels()), bb);
}

