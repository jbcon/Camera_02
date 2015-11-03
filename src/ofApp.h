#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxDelaunay.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        void drawBlobMesh(const ofxCvBlob &blob);
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        ofxKinect kinect;
        ofxCvGrayscaleImage grayImg, grayFar, grayNear;
        ofxCvColorImage colorImg;
        ofxCvContourFinder conFinder;
        ofEasyCam easyCam;
        int farThreshold, nearThreshold, res;

};
