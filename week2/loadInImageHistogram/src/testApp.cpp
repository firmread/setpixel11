#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	// load the image from the data folder
	myPicture.loadImage("test.png");
	
	// set the image type to be grayscale (1 byte per pixel)
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
	
	// set background color to be white: 
	ofBackground(255, 255, 255);
	
	
	for (int i = 0; i < 256; i++){
		histogramValues[i] = 0;
	}
	
	int width = myPicture.width;
	int height = myPicture.height;
	unsigned char * pixels = myPicture.getPixels();
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			
			int pixVal = pixels[y*width + x];
			histogramValues[pixVal]++;
		}
	}
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	
	// when we draw, the drawing color "tints" the drawing, so white is best for image
	// ie, white = no tint.
	ofSetColor(255, 255, 255);
	myPicture.draw(0,0);
	
	
	int maxVal = 0;
	for (int i = 0; i < 256; i++){
		if (histogramValues[i] > maxVal){
			maxVal = histogramValues[i];
		}
	}
	
	ofSetColor(255, 0, 0);
	for (int i = 0; i < 256; i++){
		
		float pct = (float)histogramValues[i] / (float)maxVal;
		ofLine(i, ofGetHeight(), i, ofGetHeight() - (pct*200));
	}
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

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

