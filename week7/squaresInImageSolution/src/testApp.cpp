#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	// set background color to be white: 
	ofBackground(255, 255, 255);
	
	// this prevents banding on mac (vertical sync)
	ofSetVerticalSync(true);
	
	
	// load the image from the data folder
	//myPicture.loadImage("shapes.tif");
	myPicture.loadImage("brucelee1.tif");
	
	// set the image type to be grayscale (1 byte per pixel)
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
		
	// allocate pixels and texture for this image. 
	width			= myPicture.width;
	height			= myPicture.height;
	
	myPictureSquares.allocate(width, height, OF_IMAGE_GRAYSCALE);
	
	
	// get a pointer to the image data:
	unsigned char * pixels = myPicture.getPixels();
	unsigned char * pixelsSquare = myPictureSquares.getPixels();
	
	// clear the pixels in our pixelsSquare (set them all to 255)
	for(int i=0;i<width*height;i++)
		pixelsSquare[i] = 255;
	

	
	// now check each pixel from the image for a square
	
	bool foundSquare = true;
	int largestFoundSquareSize = 1;
	int largestFoundSquareStartX;
	int largestFoundSquareStartY;
	
	while(foundSquare)
	{
		foundSquare = false;
		for (int y = 0; y < height; y++){
			for (int x = 0; x < width; x++){
				
				int pixIndex = y * width + x; // get the index of where we are
				
				if(pixels[pixIndex] == 0) // if we are a black pixel, figure out the width and height of the rectangle that we are
				{
					foundSquare = true;
					
					int squareLength = 1;
					int squareHeight = 1;
					
					for(int l=x;l<width;l++) // go from our pixel to the end (or until we hit a white pixel) for the initial row
					{
						int lengthPixIndex = y * width + l; //figure out where we are
						
						if(pixels[lengthPixIndex] < 255) //if the pixel we are looking at is black
						{
							squareLength++; //increase our length
						}
						else //otherwise, stop looking at pixels
							break; //break will break us out of any loop we are in,	
					}
					
					//now look vertially, and for each black pixel down, check each row entirely to make sure its the same size across
					for(int h=y;h<height;h++) // go from our pixel to the end (or until we hit a white pixel)
					{
						int heightPixIndex = h * width + x; //figure out where we are
						
						if(pixels[heightPixIndex] < 255) //if the pixel we are looking at is black
						{
							squareHeight++; //increase our height
							
							int tempLength = 1; // check each row
							
							for(int l=x;l<x+squareLength;l++) // go from our pixel to the maximum length we've found so far (or until we hit a white pixel) for each y value
							{
								int lengthPixIndex = h * width + l; //figure out where we are
								
								if(pixels[lengthPixIndex] < 255) //if the pixel we are looking at is black
								{
									tempLength++; //increase our length
								}
								else //otherwise, stop looking at pixels
								{
									break; //break will break us out of any loop we are in,	
								}
							}
							
							if(tempLength < squareLength) //if we're smaller, shrink the square
								squareLength=tempLength;
						}
						else //otherwise, stop looking at pixels
							break; //break will break us out of any loop we are in,
					}
					
					//now that we have length and width, set them both to the smaller one (since we're looking for squares only)
					int squareSize = MIN(squareLength, squareHeight);
					
					
					if(squareSize >= largestFoundSquareSize) // if the size of our square is the largest square in the image so far, update that information
					{
						largestFoundSquareStartX = x;
						largestFoundSquareStartY = y;
						largestFoundSquareSize = squareSize;
					}
		
				}
			}
		}
		
		if(foundSquare) //if we've found a square, move the one we've found (since it's the largest), and then go through the image again)
		{
			//now that we know how big our square is, go through again and remove it from the origional image, and then add it to the myPictureSquares
			for(int _x = largestFoundSquareStartX; _x < largestFoundSquareStartX+largestFoundSquareSize; _x++) //from our start x, to the length of the square
			{
				for(int _y = largestFoundSquareStartY; _y < largestFoundSquareStartY+largestFoundSquareSize; _y++) //from our start, y to the height of the square
				{
					int squarePixIndex = _y * width + _x; //figure out where we are
					
					pixels[squarePixIndex] = 255; // set the pixel in the origional image to white
					
					if(_x == largestFoundSquareStartX || _y == largestFoundSquareStartY || _x == largestFoundSquareStartX+largestFoundSquareSize-1 || _y == largestFoundSquareStartY+largestFoundSquareSize-1) // if we're on one of the square's edges
						pixelsSquare[squarePixIndex] = 255; // set the pixel in our pixel storage to white
					else
						pixelsSquare[squarePixIndex] = 0; // otherwise set the pixel in our pixel storage to black, this is how we get borders
				}
			}

			largestFoundSquareSize = 1; //reset found square size
		}
	}
	
	
	//myPicture.update(); //dont update the orig image, it has nothing in it anymore
	myPictureSquares.update();
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
	myPictureSquares.draw(myPicture.width,0);
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

