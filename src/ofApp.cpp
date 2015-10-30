#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    kinect.setRegistration(true);
    // ofSetLogLevel(OF_LOG_VERBOSE);

    kinect.init();
    kinect.open();
    grayImg.allocate(kinect.width, kinect.height);
    colorImg.allocate(kinect.width, kinect.height);
    grayNear.allocate(kinect.width, kinect.height);
    grayFar.allocate(kinect.width, kinect.height);

    nearThreshold = 255;
    farThreshold = 150;


    // point cloud resolution
    res = 2;
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();

    if (kinect.isFrameNew()){
        grayImg.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        colorImg.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
        grayNear = grayImg;
        grayFar = grayImg;
        grayNear.threshold(nearThreshold, true);
        grayFar.threshold(farThreshold);
        cvAnd(grayNear.getCvImage(), grayFar.getCvImage(), grayImg.getCvImage(), NULL);

        grayImg.flagImageChanged();

        conFinder.findContours(grayImg, 200, (kinect.width * kinect.height)/2, 10, false);

    }
}

//--------------------------------------------------------------
void ofApp::draw(){
     grayImg.draw(0,0);
     conFinder.draw();
    // determine valid points in blob
    easyCam.begin();
    for (int i = 0; i < conFinder.nBlobs; i++){
        drawBlobMesh(conFinder.blobs[i]);
    }
    easyCam.end();
}


void ofApp::drawBlobMesh(const ofxCvBlob &blob){
    ofRectangle rect = blob.boundingRect;
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_POINTS);
    for (int j = rect.y; j < rect.getMaxX(); j += 1){
        for (int i = rect.x; i < rect.getMaxY(); i += 1){
            ofColor c = grayImg.getPixelsRef().getColor(i, j);
            if (kinect.getDistanceAt(i, j) > 0 && c != ofColor::black){
                mesh.addColor(kinect.getColorAt(i,j));
				mesh.addVertex(kinect.getWorldCoordinateAt(i, j));
            }
        }
    }

    ofScale(1, -1, -1);
	ofTranslate(0, 0, -1000); // center the points a bit
	ofEnableDepthTest();
	mesh.draw();
	ofDisableDepthTest();
	ofPopMatrix();
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
