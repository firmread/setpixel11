#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	camWidth 	= 48;	// try to grab at this size. 
	camHeight 	= 36;	// it's so small because we dont need that much information since we're messing with the image instead of skipping pixels later, im just starting with a smaller image
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	ofSetVerticalSync(true);
	
	ofBackground(0, 0, 0);
}

//--------------------------------------------------------------
void testApp::update(){
	vidGrabber.grabFrame();
}

//--------------------------------------------------------------
void testApp::draw(){
	
	int gridSquareWidth = ofGetWidth()/camWidth; // the width of each square.. basically we're dividing the whole screen by the number of pixels in our webcam grab
	int gridSquareWidthThird = gridSquareWidth/3; // we need to know what a 3rd of the width of each square is also, since we'll be drawing 3 graph bars in each sq, one for each channel
	int gridSquareHeight = ofGetHeight()/camHeight;
	
	unsigned char * pixels = vidGrabber.getPixels(); // get the pixels of the camera
	
	for(int x=0; x<camWidth; x++)
	{
		for(int y=0; y<camHeight; y++)
		{
			int colorIndex = (y * camWidth + x) * 3; // normal y*width+x, except because there are 3 channels per each color, we have to multiply the whole thing by 3
			
			int mappedValue;
			
			for(int c=0; c<3; c++) // go through each channel
			{
				mappedValue = ofMap(pixels[colorIndex + c], 0, 255, 0, gridSquareHeight); // map the value of each channel from 0-255 into 0 to the height of each grid spare
				
				if(c==0) //figure out which channel we're looking at, and then set the color to just the strength of that channel
					ofSetColor(pixels[colorIndex + 0], 0, 0);
				else if(c==1)
					ofSetColor(0, pixels[colorIndex + 1], 0);
				else
					ofSetColor(0, 0, pixels[colorIndex + 2]);
				
				//draw a rectangle in the right place
				ofRect(x*gridSquareWidth + gridSquareWidthThird*c, y*gridSquareHeight + gridSquareHeight, gridSquareWidthThird, -mappedValue);
			}
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

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}