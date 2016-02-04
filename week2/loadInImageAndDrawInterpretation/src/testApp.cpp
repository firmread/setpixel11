#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	// load the image from the data folder
	myPicture.loadImage("test.png");
	
	// set the image type to be grayscale (1 byte per pixel)
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
	
	// set background color to be white: 
	ofBackground(0, 0, 0);
	
	// this prevents banding on mac (vertical sync)
	ofSetVerticalSync(true);
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
	
	// get a pointer to the image data:
	unsigned char * pixelsFromImage = myPicture.getPixels();
	int width = myPicture.width;
	int height = myPicture.height;
	
	
	// copy the pixels in and upload
	for (int x = 0; x < width; x+=20){
		for (int y = 0; y < height; y+=20){
			
			int pixIndex = y * width + x;
			int pixVal = pixelsFromImage[pixIndex];
			float pct = (float)pixVal / 255.0f;
			ofCircle(width + 10 + x, y, 10*pct);
		}
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

