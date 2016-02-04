#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	// load the image from the data folder
	myPicture.loadImage("test.png");
	
	// set the image type to be grayscale (1 byte per pixel)
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
	
	// allocate opencv, load in: 
	
	myPictureAsCvImage.allocate(myPicture.width, myPicture.height);
	myPictureAsCvImage.setFromPixels(myPicture.getPixels(),myPicture.width, myPicture.height);
	
	// set background color to be white: 
	ofBackground(255, 255, 255);
	
	
	panel.setup("cv settings", 720, 0, 300, 748);
	panel.addPanel("control", 1, false);
	
	panel.setWhichPanel("control");
	panel.addToggle("blur ", "B_BLUR", false);
	panel.addSlider("threshold ", "THRESHOLD", 127, 0, 255, true);
	
	panel.loadSettings("cvSettings.xml");
}

//--------------------------------------------------------------
void testApp::update(){
		
	panel.update();
	
	
	bool bBlur =  panel.getValueB("B_BLUR");
	int threshold = panel.getValueI("THRESHOLD");

	myPictureAsCvImage.setFromPixels(myPicture.getPixels(),myPicture.width, myPicture.height);
	
	if (bBlur){
		myPictureAsCvImage.blur(33);
	}
	
	myPictureAsCvImage.threshold(threshold);

}

//--------------------------------------------------------------
void testApp::draw(){
	
	// when we draw, the drawing color "tints" the drawing, so white is best for image
	// ie, white = no tint.
	ofSetColor(255, 255, 255);
	myPictureAsCvImage.draw(0,0);
	
	panel.draw();
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
	panel.mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	panel.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	panel.mouseReleased();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

