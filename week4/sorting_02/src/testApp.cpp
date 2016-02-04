#include "testApp.h"



// this is the "comparison" function
int compare( const void *a,  const void *b){			
	
	// the const void means -- this function doesn't have a "set" type -- 
	// it's very C style. 
	
	// we first (step1) convert a and b to (unsigned char) pointers
	// (step2) we dereference to get the values held by a and b
	// I know this is crazy !!  but it works and is fast !! 
	// for those in the know, STL vector < > has sorting functionality too
	// I will show you that at some point....
	// kk.
	
	unsigned char *aPtr = ( unsigned char *)a;	// (step1) casting pointer types to be of the type unsigned char *
	unsigned char *bPtr = ( unsigned char *)b;
	unsigned char valuea = *aPtr;				// (step2) get the value out of ptr a and b...
	unsigned char valueb = *bPtr;
	if (valuea > valueb) return 1;
	else return -1;
}


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
	
	// allocate pixels and texture for this image. 
	width = myPicture.width;
	height = myPicture.height;
	
	myPictureSorted.allocate(width, height, OF_IMAGE_GRAYSCALE);
	unsigned char * sortedPixels = myPictureSorted.getPixels();
	
	
	// get a pointer to the image data:
	unsigned char * pixelsFromImage = myPicture.getPixels();
	
	// copy the pixels in and upload
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			
			int pixIndex = y * width + x;
			sortedPixels[pixIndex] = pixelsFromImage[pixIndex];
		}
	}
	
	qsort(sortedPixels, width*height, sizeof(unsigned char), compare);
	
	myPictureSorted.update();
	
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
	
	myPictureSorted.draw(myPicture.width, 0);
	
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

