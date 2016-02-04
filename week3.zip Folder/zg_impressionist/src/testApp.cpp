#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	camWidth 	= 80;	// try to grab at this size. 
	camHeight 	= 60;	// it's so small because we dont need that much information since we're messing with the image instead of skipping pixels later, im just starting with a smaller image
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	ofSetVerticalSync(true);
	
	ofBackground(0, 0, 0);
	
	//this application attempts to find pixels of a similar color around each pixel in the image. if it finds any, it draws a line of the original pixels color to the similar pixel
	
	//messing with these two can generate really different stuff, although it can also make the program run really slowly
	comparisonThreshold = 3; // threshold for agreeing that a pixel is a similar color
	comparisonDistance = 12; // distance to check away from starting pixel
}

//--------------------------------------------------------------
void testApp::update(){
	vidGrabber.grabFrame();
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofSetLineWidth(10); // set line width really high
	
	unsigned char * pixels = vidGrabber.getPixels(); // get the pixels of the camera
	
	int gridSquareWidth = ofGetWidth()/camWidth; // the width of each square.. basically we're dividing the whole screen by the number of pixels in our webcam grab
	int gridSquareHeight = ofGetHeight()/camHeight;
	
	for(int x=0; x<camWidth; x++)
	{
		for(int y=0; y<camHeight; y++)
		{
			int colorIndex = (y * camWidth + x) * 3;
			int colorAvg = pixels[colorIndex] + pixels[colorIndex + 1] + pixels[colorIndex + 2]; // add all the chanels together
			colorAvg /= 3; //and divide by 3
			
			int r = 0;
			
			// look through all the pixels around my pixel in a square, use MIN() and MAX() to make sure we don't accidentally try and access a pixel outside of the image
			for(int x2 = MAX(x-comparisonDistance, 0); x2 < MIN(x+comparisonDistance, camWidth); x2++)
			{
				for(int y2 = MAX(y-comparisonDistance, 0); y2 < MIN(y+comparisonDistance, camHeight); y2++)
				{
					if(x2 != x && y2 != y) //if we're not looking at our original pixel
					{
						int newColorIndex = (y2 * camWidth + x2) * 3;
						int newColorAvg = pixels[newColorIndex] + pixels[newColorIndex + 1] + pixels[newColorIndex + 2]; // add all the chanels together
						newColorAvg /= 3; //and divide by 3
						
						if(ABS(colorAvg - newColorAvg) < comparisonThreshold) // if the colors are similar enough
						{
							//draw a line between them of the original pixels color
							ofSetColor(pixels[colorIndex + 0], pixels[colorIndex + 1], pixels[colorIndex + 2]);
							
							r = ofRandomf()*10; // get a random number between -10 and 10 to add to our line points to make things move a bit
							
							//actually draw the line
							ofLine(x*gridSquareWidth + r, y*gridSquareHeight + r, x2*gridSquareWidth + r, y2*gridSquareHeight + r);
						}
					}
				}
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