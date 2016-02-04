#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	 
	
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);

        
    colorImg.allocate(320,240);
	grayImage.allocate(320,240);

	
	panel.setup("cv settings", 720, 0, 300, 748);
	panel.addPanel("control", 1, false);
	
	panel.setWhichPanel("control");
	panel.addSlider("scale haar ", "SCALEHAAR", 1.2, 1, 3.0, false);
	
	
	// load the correct xml file from the bin/data/haarXML/ folder
	
	haarFinder.setup("haarXML/haarcascade_frontalface_default.xml");

	
	ofBackground(0,0,0);
}

//--------------------------------------------------------------
void testApp::update(){
	
	
    
	panel.update();
	
	float scaleHaar = panel.getValueF("SCALEHAAR");
	haarFinder.setScaleHaar(scaleHaar);
	
	bool bNewFrame = false;
	vidGrabber.grabFrame();
	bNewFrame = vidGrabber.isFrameNew();

	if (bNewFrame){
		colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
        grayImage = colorImg;
		haarFinder.findHaarObjects(grayImage);
	}
}

//--------------------------------------------------------------
void testApp::draw(){

	// draw the incoming & the grayscale
	ofSetColor(0xffffff);
	colorImg.draw(20,20);	
	grayImage.draw(360,20);
	
	// how many matches did you find?
	int numMatches = haarFinder.blobs.size();
	
	
	// drawing the matches
	glPushMatrix();
	glTranslatef(20, 20, 0);
	for(int i = 0; i < numMatches; i++){
		float x = haarFinder.blobs[i].boundingRect.x;
		float y = haarFinder.blobs[i].boundingRect.y;
		float w = haarFinder.blobs[i].boundingRect.width;
		float h = haarFinder.blobs[i].boundingRect.height;
		
		float cx = haarFinder.blobs[i].centroid.x;
		float cy = haarFinder.blobs[i].centroid.y;
		
		ofSetColor(0x00FF00);
		ofSetLineWidth(4);
		ofNoFill();
		ofEllipse(x+w/2, y+h/2, w, 4*h/3);

		ofSetColor(0xFFFFFF);
		ofDrawBitmapString(ofToString(i), cx, cy);
		
	}
	glPopMatrix();
	
	
	ofSetLineWidth(1);
	
	// drawing some info
	ofSetColor(0xffffff);
	string reportStr= "matches found: "+ ofToString(numMatches, 0)+", framerate: "+ofToString(ofGetFrameRate(),0);
	ofDrawBitmapString(reportStr, 20, 10);

	panel.draw();
	
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	switch (key){
		case 's':
			vidGrabber.videoSettings();
		break;
	}
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
void testApp::mouseReleased(){
	panel.mouseReleased();
}

