#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	// set background color to be white: 
	ofBackground(255, 255, 255);
	
	// this prevents banding on mac (vertical sync)
	ofSetVerticalSync(true);
	
	// load the image from the data folder
	myPicture.loadImage("test.png");
	
	// set the image type to be grayscale (1 byte per pixel)
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
	
	//allocate an image the same size
	invertedPicture.allocate(myPicture.width, myPicture.height, OF_IMAGE_GRAYSCALE);
	
	// grab "pointers" to the pixels of the original and destination images. 
	unsigned char * origPixels =  myPicture.getPixels();
	unsigned char * destPixels =  invertedPicture.getPixels();
	
	int width = myPicture.width;
	int height = myPicture.height;
	
	// copy the pixels and invert
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			
			int pixIndex = y * width + x;
			destPixels[pixIndex] = 255 - origPixels[pixIndex];
		}
	}
	
	// update makes sure the pixels are updated to the texture 
	// (if we alter the pixels of an image, we need to update to visually see the changes)
	invertedPicture.update();
	
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
	
	invertedPicture.draw(myPicture.width, 0);
	
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

