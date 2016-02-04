#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofBackground(255, 255, 255);
	ofSetVerticalSync(true);

	// ---- (1) pick a width and height: 
	
	width = 400;
	height = 250;
	
	// ---- (2) allocate an image
	
	image.allocate(width, height, OF_IMAGE_GRAYSCALE);
	
	
	// ---- (3) grab a "pointers" to the pixels of the image
	
	unsigned char * pixels =  image.getPixels();
	
	// ---- (4) put black values into memory...  be careful with your for loops when you start to alter memory
	
	for (int i = 0; i < width * height; i++){
		pixels[i] = 0;
	}
	
	// ---- (5) tell the image to update it's texture from it's pixels so that we can see the change
	
	image.update();
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	
	unsigned char * pixels =  image.getPixels();
	// find points that are within a certain distance of the mouse:
	
	// note this is SLOW ;)
	
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			
			int diffx = (i - mouseX);
			int diffy = (j - mouseY);
			float distance = sqrt(diffx*diffx + diffy*diffy);
			if (distance < 50){
				//pixels[j * width + i] = 255;
				//	percentage based stuff to show in class. 
				float pct = distance / 50.0f;
				pixels[j * width + i] = MIN(255, pixels[j * width + i] + 255 * (1-pct));
			}
		}
	}
	
	
	// uncomment me for the fade routine.

	 for (int i = 0; i < width; i++){
		 for (int j = 0; j < height; j++){
			 pixels[j * width + i] = MAX(0, pixels[j * width + i]-2);
		 }
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

