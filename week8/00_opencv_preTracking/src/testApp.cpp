#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	// setup video grabber:
	//video.loadMovie("Swarm_EindhovenTest_Watec_two-visitors.mov");
	//video.play();
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
	panel.setWhichColumn(0);
	panel.addToggle("learn background ", "B_LEARN_BG", true);
	panel.addSlider("threshold ", "THRESHOLD", 127, 0, 255, true);
	
	panel.addSlider("nDilations ", "N_DILATIONS", 2, 0, 20, true);
	panel.addSlider("nErosions ", "N_EROSION", 0, 0, 20, true);
	
	panel.addSlider("minBlobSize ", "MIN_BLOB_SIZE", 50, 0, width*height*0.2f, true);
	panel.addSlider("maxBlobSize ", "MAX_BLOB_SIZE", 20000, 0, width*height*0.5f, true);
	panel.addSlider("nBlobs to find ", "N_BLOBS_TO_FIND", 10, 0, 15, true);
	
	
	
	panel.loadSettings("cvSettings.xml");
}

//--------------------------------------------------------------
void testApp::update(){
		
	panel.update();
	
	
	bool bLearnBg			= panel.getValueB("B_LEARN_BG");
	int threshold			= panel.getValueI("THRESHOLD");
	int nDilations			= panel.getValueI("N_DILATIONS");
	int nErosions			= panel.getValueI("N_EROSION");
	int maxOperations = MAX(nDilations, nErosions);
	
	int minBlobSize			= panel.getValueI("MIN_BLOB_SIZE");
	int maxBlobSize			= panel.getValueI("MAX_BLOB_SIZE");
	int bBlobsTofind		= panel.getValueI("N_BLOBS_TO_FIND");
	
	
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
		videoDiffImage.threshold(threshold);
		
		for (int i = 0; i < maxOperations; i++){
			
			
			if (i < nDilations)	videoDiffImage.dilate();
			if (i < nErosions)	videoDiffImage.erode();
			
		}
		
		contourFinder.findContours(	videoDiffImage, minBlobSize,maxBlobSize,bBlobsTofind,false, true);
		
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofSetColor(255, 255, 255);
	videoGrayscaleCvImage.draw(20,20, 320,240);
	videoBgImage.draw(320+40, 20, 320, 240);
	videoDiffImage.draw(20,240+40, 640,480);
	
	contourFinder.draw(20,240+40,640,480);
	
	for (int i = 0; i < contourFinder.nBlobs; i++){
		ofDrawBitmapString("blob id:" + ofToString(i), contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y);
	}
	
	
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

