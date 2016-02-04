#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofBackground(255, 255, 255);
	

	// ---- (1) pick a width and height: 
	
	width = 400;
	height = 250;
	
	// ---- (2) allocate an image
	
	image.allocate(width, height, OF_IMAGE_GRAYSCALE);
	
	
	// ---- (3) grab a "pointers" to the pixels of the image
	
	unsigned char * pixels =  image.getPixels();
	
	// ---- (4) put random values into memory...  be careful with your for loops when you start to alter memory
	
	for (int i = 0; i < width * height; i++){
		pixels[i] = (int)ofRandom(0,255);
	}
	
	// ---- (5) tell the image to update it's texture from it's pixels so that we can see the change
	
	image.update();
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	unsigned char * pixels =  image.getPixels();
	
	for (int i = 0; i < width * height; i++){
		pixels[i] = (int)ofRandom(127-mouseX, 127+mouseX);
	}
	
	image.update();

}

//--------------------------------------------------------------
void testApp::draw(){
	
	image.draw(0,0);
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

