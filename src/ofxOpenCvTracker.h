#pragma once

#include "ofMain.h"
#include "opencv2/opencv_modules.hpp"
//#if defined(HAVE_OPENCV_DNN) && defined(HAVE_OPENCV_DATASETS)

#include "opencv2/datasets/track_alov.hpp"
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;
using namespace cv::datasets;

inline cv::Ptr<cv::Tracker> createTrackerByName(cv::String name)
{
    cv::Ptr<cv::Tracker> tracker;
    
    if (name == "KCF")
        tracker = cv::TrackerKCF::create();
//    else if (name == "TLD")
//        tracker = cv::TrackerTLD::create();
//    else if (name == "BOOSTING")
//        tracker = cv::TrackerBoosting::create();
//    else if (name == "MEDIAN_FLOW")
//        tracker = cv::TrackerMedianFlow::create();
//    else if (name == "MIL")
//        tracker = cv::TrackerMIL::create();
    else if (name == "GOTURN")
        tracker = cv::TrackerGOTURN::create();
//    else if (name == "MOSSE")
//        tracker = cv::TrackerMOSSE::create();
    else if (name == "CSRT")
        tracker = cv::TrackerCSRT::create();
    else
        CV_Error(cv::Error::StsBadArg, "Invalid tracking algorithm name\n");
    

    return tracker;
}

class ofxOpenCvTracker{
public:
    ofxOpenCvTracker();
    ~ofxOpenCvTracker();
    void setup();
    void setup(string _tracker_name);
    void update(ofPixels &_p);
    void update(ofPixels &_p, int _tracker_image_width, int _tracker_image_height);
    void set(ofPixels &_p, ofRectangle _r);
    void set(ofPixels &_p, ofRectangle _r, int _tracker_image_width, int _tracker_image_height);
    ofRectangle getTrackerRectangle();
    bool getFound();
    cv::Mat toCV(ofPixels &pix);

    string tracker_name;
    cv::Ptr<Tracker> tracker;
    cv::Rect bb;
    ofRectangle r_selected;
    int tracker_image_width;
    int tracker_image_height;
    int image_width;
    int image_height;
    bool is_found;
private:
};

