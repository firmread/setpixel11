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
	
	// allocate pixels and texture for this image. 
	width			= myPicture.width;
	height			= myPicture.height;
	
	myPictureBlurred.allocate(width, height, OF_IMAGE_GRAYSCALE);
	
	// get a pointer to the image data:
	unsigned char * pixels = myPicture.getPixels();
	unsigned char * pixelsBlurred	= myPictureBlurred.getPixels();
	
	// now, let's blur from pixels into pixelsBlurred:
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			
			// not accounting for edges. 
			/*
			int nw = ((y-1) * width + (x-1));
			int n_ = ((y-1) * width + (x  ));
			int ne = ((y-1) * width + (x+1));
			int _w = ((y  ) * width + (x-1));
			int me = ((y  ) * width + (x  ));
			int _e = ((y  ) * width + (x+1));
			int sw = ((y+1) * width + (x-1));
			int s_ = ((y+1) * width + (x  ));
			int se = ((y+1) * width + (x+1));
			*/
			
			int pixIndex = y * width + x;
			
			// deal with the edges !! :	
			// (using min and max to make sure that we don't go past the 0,0 or the maximum width/height of the image)
			int x_m_1 = MAX(0, x-1);
			int x_p_1 = MIN(width-1, x+1);
			int y_m_1 = MAX(0, y-1);
			int y_p_1 = MIN(height-1, y+1);
			
			//------------------
			
			int nw = (y_m_1 * width + x_m_1);
			int n_ = (y_m_1 * width + x    );
			int ne = (y_m_1 * width + x_p_1);
			int _w = (y     * width + x_m_1);
			int me = (y     * width + x    );
			int _e = (y     * width + x_p_1);
			int sw = (y_p_1 * width + x_m_1);
			int s_ = (y_p_1 * width + x    );
			int se = (y_p_1 * width + x_p_1);
			
			int newValue =	pixels[ne] + pixels[n_] + pixels[nw] + pixels[_e] + pixels[me] + pixels[_w] + 
							pixels[se] + pixels[s_] + pixels[sw];
			
			newValue /= 9; //each value is the average of all the pixels around it
			
			pixelsBlurred[pixIndex]  = newValue;
		}
	}
	
	
	
	
	myPictureBlurred.update();
		
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
	
	myPictureBlurred.draw(myPicture.width, 0);
	
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

