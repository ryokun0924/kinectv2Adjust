#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    ofxPanel panel;
    ofxSlider <int> minDistance;
    ofxSlider <int> maxDistance;
    ofxSlider <int> kinectFrameRate;
    ofxSlider <int> ofFrameRate;
    
    ofxSlider <int> minDetectSize;
    ofxSlider <int> maxDetectSize;
    ofxSlider <int> maxDetectNumber;
    
    void onMinDistanceChanged(int& num);
    void onMaxDistanceChanged(int& num);

    void onKinectFrameRateChanged(int& num);
    void onOfFrameRateChanged(int& num);

    //値が変わった時に保存だけすればよい変数のリスナ
    void onValueChanged(int& num);
    
    ofxKinectV2 kinect;
    ofTexture texDepth;
    ofTexture texRGB;
    
    //for detect hand
    ofxCvContourFinder contourFinder;
    ofxCvGrayscaleImage grayImage;
    
		
};
