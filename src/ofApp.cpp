#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    if( !ofFile::doesFileExist("11to16.bin") ){
        ofSystemAlertDialog("Make sure you have 11to16.bin, xTable.bin and zTable.bin in your data folder!");
        ofExit();
    }
    
    ofBackground(30, 30, 30);
    
    panel.setup("distance in mm", "settings.xml", 540, 100);
    panel.add(minDistance.setup("minDistance",100,0,12000));
    panel.add(maxDistance.setup("maxDistance",6000,0,12000));

    panel.add(minDetectSize.setup("minDetectSize",2,0,1000));
    panel.add(maxDetectSize.setup("maxDetectSize",1000,0,300000));
    panel.add(maxDetectNumber.setup("maxDetectNumber",10,0,300));

//    panel.add(kinectFrameRate.setup("kinectFrameRate",30,0,120));
    panel.add(ofFrameRate.setup("ofFrameRate",60,0,120));
    panel.loadFromFile("settings.xml");
    
    
    
    kinect.minDistance = minDistance;
    kinect.maxDistance = maxDistance;
    
    minDistance.addListener(this, &ofApp::onMinDistanceChanged );
    maxDistance.addListener(this, &ofApp::onMaxDistanceChanged );
    minDetectSize.addListener(this, &ofApp::onValueChanged );
    maxDetectSize.addListener(this, &ofApp::onValueChanged );
    maxDetectNumber.addListener(this, &ofApp::onValueChanged );
    ofFrameRate.addListener(this, &ofApp::onOfFrameRateChanged);

    ofSetFrameRate(ofFrameRate);
    kinect.open();
    grayImage.allocate(kinect.getDepthPixels().getWidth(),kinect.getDepthPixels().getHeight());

}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
    if( kinect.isFrameNew() ){
        texDepth.loadData( kinect.getDepthPixels() );
//        texRGB.loadData( kinect.getRgbPixels() );

        grayImage.setFromPixels( kinect.getDepthPixelsPointer()->getPixels() , kinect.getDepthPixelsPointer()->getWidth(), kinect.getDepthPixelsPointer()->getHeight() );
        contourFinder.findContours(grayImage, minDetectSize, maxDetectSize, maxDetectNumber , false);
        
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("ofxKinectV2: Work in progress addon.\nBased on the excellent work by the OpenKinect libfreenect2 team\n\n-Only supports one Kinect v2 at a time. \n-Requires USB 3.0 port ( superspeed )\n-Requires patched libusb. If you have the libusb from ofxKinect ( v1 ) linked to your project it will prevent superspeed on Kinect V2", 10, 14);
    
    texDepth.draw(10, 100);
//    texRGB.draw(10, 110 + texDepth.getHeight(), 1920/4, 1080/4);


    contourFinder.draw(10,100, texDepth.getWidth(),texDepth.getHeight());
    
    panel.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
void ofApp::onMinDistanceChanged(int& num){
    panel.saveToFile("settings.xml");
    kinect.minDistance = minDistance;
}
void ofApp::onMaxDistanceChanged(int& num){
      panel.saveToFile("settings.xml");
     kinect.maxDistance = maxDistance;
}
void ofApp::onValueChanged(int& num){
          panel.saveToFile("settings.xml");
}

void ofApp::onOfFrameRateChanged(int& num){
    ofSetFrameRate(ofFrameRate);
    panel.saveToFile("settings.xml");
}

