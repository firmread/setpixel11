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
	videoGrayscaleCvImagePreWarp.allocate(width, height);
	// set background color to be white: 
	ofBackground(255, 255, 255);
	
	
	srcPts[0].set(0,0);
	srcPts[1].set(width,0);
	srcPts[2].set(width,height);
	srcPts[3].set(0,height);
	
	dstPts[0].set(0,0);
	dstPts[1].set(width,0);
	dstPts[2].set(width,height);
	dstPts[3].set(0,height);
	
	panel.setup("cv settings", 720, 0, 300, 748);
	panel.addPanel("control", 1, false);
	
	panel.addPanel("warping", 1, false);
	
	
	panel.setWhichPanel("control");
	panel.setWhichColumn(0);
	panel.addToggle("learn background ", "B_LEARN_BG", true);
	panel.addSlider("threshold ", "THRESHOLD", 127, 0, 255, true);
	
	panel.addSlider("min blob size ", "MIN_BLOB_SIZE", 100, 0, width*height, true);
	panel.addSlider("max blob size ", "MAX_BLOB_SIZE", 10000, 0, width*height, true);
	panel.addSlider("max num blobs to find ", "N_BLOBS_CONSIDERED", 3, 0, 20, true);
	
	
	panel.setWhichPanel("warping");
	panel.addSlider2D("pta", "CV_MANAGER_PANEL_VIDEO_PTA", 0, 0, 0, width, 0, height, true);
	panel.addSlider2D("ptb", "CV_MANAGER_PANEL_VIDEO_PTB", width, 0, 0, width, 0, height, true);
	panel.addSlider2D("ptc", "CV_MANAGER_PANEL_VIDEO_PTC", width, height, 0, width, 0, height, true);
	panel.addSlider2D("ptd", "CV_MANAGER_PANEL_VIDEO_PTD", 0, height, 0, width, 0, height, true);
	
	
	
	panel.loadSettings("cvSettings.xml");
}

//--------------------------------------------------------------
void testApp::update(){
		
	panel.update();
	
	
	srcPts[0].set( panel.getValueI("CV_MANAGER_PANEL_VIDEO_PTA", 0), panel.getValueI("CV_MANAGER_PANEL_VIDEO_PTA", 1));
	srcPts[1].set( panel.getValueI("CV_MANAGER_PANEL_VIDEO_PTB", 0), panel.getValueI("CV_MANAGER_PANEL_VIDEO_PTB", 1));
	srcPts[2].set( panel.getValueI("CV_MANAGER_PANEL_VIDEO_PTC", 0), panel.getValueI("CV_MANAGER_PANEL_VIDEO_PTC", 1));
	srcPts[3].set( panel.getValueI("CV_MANAGER_PANEL_VIDEO_PTD", 0), panel.getValueI("CV_MANAGER_PANEL_VIDEO_PTD", 1));
	
	bool bLearnBg			= panel.getValueB("B_LEARN_BG");
	int threshold			= panel.getValueI("THRESHOLD");
	int minBlobSize			= panel.getValueI("MIN_BLOB_SIZE");
	int maxBlobSize			= panel.getValueI("MAX_BLOB_SIZE");
	int nBlobsConsidered	= panel.getValueI("N_BLOBS_CONSIDERED");

	
	video.update();
	
	if (video.isFrameNew()){
		
		videoColorCvImage.setFromPixels(video.getPixels(), width, height);
		
		videoGrayscaleCvImagePreWarp = videoColorCvImage;
		videoGrayscaleCvImage.warpIntoMe(videoGrayscaleCvImagePreWarp, srcPts, dstPts);
		
		//videoGrayscaleCvImage = videoColorCvImage;
		
		if (bLearnBg ){ 
			videoBgImage = videoGrayscaleCvImage;
			panel.setValueB("B_LEARN_BG", false);
		}
		
		if (ofGetElapsedTimef() < 1.5){
			videoBgImage = videoGrayscaleCvImage;
		}
		
		videoDiffImage.absDiff(videoGrayscaleCvImage, videoBgImage);
		videoDiffImage.threshold(threshold);
		
		contourFinder.findContours(videoDiffImage, minBlobSize, maxBlobSize, nBlobsConsidered, false, true);
		
		
	
		
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
	
	
	videoGrayscaleCvImagePreWarp.draw(20,20, 320,240);
	videoGrayscaleCvImage.draw(320+40, 20, 320, 240);
	videoBgImage.draw(20,240+40);
	videoDiffImage.draw(320+40,240+40);
	contourFinder.draw(320+40,240+40);
	panel.draw();
	
	ofSetColor(255, 0, 0);
	ofPushMatrix();
	ofTranslate(20, 20, 0);
	ofBeginShape();
	ofNoFill();
	for (int i = 0; i < 4; i++){
		ofVertex(srcPts[i].x, srcPts[i].y); 
	}
	ofEndShape(true);
	
	ofFill();
	for (int i = 0; i < 4; i++){
		ofCircle(srcPts[i].x, srcPts[i].y, 4); 
	}
	
	ofPopMatrix();
	
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

