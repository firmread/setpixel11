#ifndef _TEST_APP
#define _TEST_APP


#define OF_ADDON_USING_OFXOPENCV

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxControlPanel.h"

typedef struct {
	
	ofPoint		pos;
	ofPoint		posSmooth;
	float		width;
	float		widthSmooth;

	float		energy;
	int			nFramesAlive;
	bool		bFoundThisFrame;
	int			whoThisFrame;
	int			id;
	
} tracker;


class testApp : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();

      
		ofVideoGrabber			vidGrabber;
        ofxCvColorImage			colorImg;
        ofxCvGrayscaleImage 	grayImage;
		ofxCvHaarFinder			haarFinder;
		ofxControlPanel			panel;
	
		// this will store all trackers...
		vector < tracker >		trackerObjects;
		int						idCount;
		
		ofImage					maskImage[3];
};

#endif
