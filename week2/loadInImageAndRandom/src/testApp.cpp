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
	modifiedPicture.allocate(myPicture.width, myPicture.height, OF_IMAGE_GRAYSCALE);
	
	int width = myPicture.width;
	int height = myPicture.height;
	
	// grab "pointers" to the pixels of the original and destination images. 
	unsigned char * origPixels =  myPicture.getPixels();
	unsigned char * destPixels =  modifiedPicture.getPixels();
	
	// copy the pixels in and upload
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			
			int pixIndex = y * width + x;
			destPixels[pixIndex] = origPixels[pixIndex];
		}
	}
	
	modifiedPicture.update();
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	int width = myPicture.width;
	int height = myPicture.height;
	
	
	// grab "pointers" to the pixels of the original and destination images. 
	unsigned char * origPixels =  myPicture.getPixels();
	unsigned char * destPixels =  modifiedPicture.getPixels();
	
	// copy the pixels in and upload
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			
			int pixIndex = y * width + x;
			int pixSource = (y + (int)ofRandom(-mouseX, mouseX)) * width + (x +  (int)ofRandom(-mouseX, mouseX));
			if (pixSource < 0) pixSource = 0;
			if (pixSource >= width*height) pixSource = width*height-1;
			destPixels[pixIndex] = origPixels[pixSource];
			
		}
	}
	
	modifiedPicture.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	

	// when we draw, the drawing color "tints" the drawing, so white is best for image
	// ie, white = no tint.
	ofSetColor(255, 255, 255);
	myPicture.draw(0,0);
	modifiedPicture.draw(myPicture.width, 0);
	
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

