#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	// setup video grabber:
	video.initGrabber(320, 240);
	
	// get the width and height, and allocate color and grayscale images: 
	width = video.width; 
	height = video.height;
	
	videoColorCvImage.allocate(width, height);
	videoGrayscaleCvImage.allocate(width, height);
	videoBgImage.allocate(width, height);
	videoDiffImage.allocate(width, height);
	
	// set background color to be white: 
	ofBackground(255, 255, 255);
	
	
	panel.setup("cv settings", 720, 0, 300, 748);
	panel.addPanel("control", 1, false);
	
	panel.setWhichPanel("control");
	panel.addToggle("learn background ", "B_LEARN_BG", true);
	panel.addSlider("threshold ", "THRESHOLD", 127, 0, 255, true);
	
	panel.addSlider("min blob size ", "MIN_BLOB_SIZE", 100, 0, width*height, true);
	panel.addSlider("max blob size ", "MAX_BLOB_SIZE", 10000, 0, width*height, true);
	panel.addSlider("max num blobs to find ", "N_BLOBS_CONSIDERED", 3, 0, 20, true);
	
	
	
	panel.loadSettings("cvSettings.xml");
}

//--------------------------------------------------------------
void testApp::update(){
		
	panel.update();
	
	
	bool bLearnBg			= panel.getValueB("B_LEARN_BG");
	int threshold			= panel.getValueI("THRESHOLD");
	int minBlobSize			= panel.getValueI("MIN_BLOB_SIZE");
	int maxBlobSize			= panel.getValueI("MAX_BLOB_SIZE");
	int nBlobsConsidered	= panel.getValueI("N_BLOBS_CONSIDERED");

	
	video.update();
	
	if (video.isFrameNew()){
		
		videoColorCvImage.setFromPixels(video.getPixels(), width, height);
		videoGrayscaleCvImage = videoColorCvImage;
		
		if (bLearnBg ){ 
			videoBgImage = videoGrayscaleCvImage;
			panel.setValueB("B_LEARN_BG", false);
		}
		
		if (ofGetElapsedTimef() < 1.5){
			videoBgImage = videoGrayscaleCvImage;
		}
		
		videoDiffImage.absDiff(videoGrayscaleCvImage, videoBgImage);
		//videoDiffImage.blur(11);
		videoDiffImage.threshold(threshold);
		
		contourFinder.findContours(videoDiffImage, minBlobSize, maxBlobSize, nBlobsConsidered, false, true);
		
		
		printf("we found %i blobs \n", contourFinder.nBlobs);
		for (int i = 0; i <  contourFinder.nBlobs; i++){
			printf("centroid of blob %i = (%f,%f) \n", i, contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y);
		}
		
		//printf(" this is my text !  %f ", ..., ...);
		
		
		/*						
		ofxCvGrayscaleImage&  input,
		int minArea,
		int maxArea,
		int nConsidered,
		bool bFindHoles,
		bool bUseApproximation
		*/						
								
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofSetColor(255, 255, 255);
	videoGrayscaleCvImage.draw(20,20, 320,240);
	videoBgImage.draw(320+40, 20, 320, 240);
	videoDiffImage.draw(20,240+40);
	contourFinder.draw(20,240+40);
	panel.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	panel.mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	panel.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	panel.mouseReleased();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

