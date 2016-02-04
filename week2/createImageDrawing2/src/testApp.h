#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		
		unsigned char * pixels;				// we do this as a pointer.  don't worry!  it's just easier to allocate
											// the memory in setup then on the stack.  will explain!
	
		int width;
		int height;
		
		ofImage	image;

};

#endif
