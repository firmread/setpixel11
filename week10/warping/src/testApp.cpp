#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){


	#ifdef _USE_LIVE_VIDEO
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(320,240);
	#else
        vidPlayer.loadMovie("fingers.mov");
        vidPlayer.play();
	#endif

    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
	grayImagePreWarp.allocate(320,240);

	bLearnBakground = true;
	threshold = 80;
	
	
	srcPts[0].set(0,0);
	srcPts[1].set(320,0);
	srcPts[2].set(320,240);
	srcPts[3].set(0,240);
	
	dstPts[0].set(0,0);
	dstPts[1].set(320,0);
	dstPts[2].set(320,240);
	dstPts[3].set(0,240);
	
	bAdjustingPoint = false;
	whichPointAdjusting = 0;
	
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);

    bool bNewFrame = false;

	#ifdef _USE_LIVE_VIDEO
       vidGrabber.grabFrame();
	   bNewFrame = vidGrabber.isFrameNew();
    #else
        vidPlayer.idleMovie();
        bNewFrame = vidPlayer.isFrameNew();
	#endif

	if (bNewFrame){

		#ifdef _USE_LIVE_VIDEO
            colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
	    #else
            colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);
        #endif

        grayImagePreWarp = colorImg;
		grayImage.warpIntoMe(grayImagePreWarp, srcPts, dstPts);
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);	// find holes
	}

	printf("%f \n", ofGetFrameRate());
}

//--------------------------------------------------------------
void testApp::draw(){

	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetColor(0xffffff);
	grayImagePreWarp.draw(20,20);
	grayImage.draw(360,20);
	grayBg.draw(20,280);
	grayDiff.draw(360,280);
	
	
	// since we are drawing at 20,20, this is offset: 
	
	ofPushMatrix();
	ofTranslate(20, 20, 0);
	ofBeginShape();
	ofNoFill();
	for (int i = 0; i < 4; i++){
		ofVertex(srcPts[i].x, srcPts[i].y); 
	}
	ofEndShape(true);
	
	ofFill();
	for (int i = 0; i < 4; i++){
		
		if (bAdjustingPoint == true && whichPointAdjusting == i) ofSetColor(255, 0, 0);
		else ofSetColor(255, 255, 255);
		
		ofCircle(srcPts[i].x, srcPts[i].y, 4); 
	}
	
	ofPopMatrix();
	
	

	// then draw the contours:

	ofFill();
	ofSetColor(0x333333);
	ofRect(360,540,320,240);
	ofSetColor(0xffffff);

	// we could draw the whole contour finder
	//contourFinder.draw(360,540);

	// or, instead we can draw each blob individually,
	// this is how to get access to them:
    for (int i = 0; i < contourFinder.nBlobs; i++){
        contourFinder.blobs[i].draw(360,540);
    }

	// finally, a report:

	ofSetColor(0xffffff);
	char reportStr[1024];
	sprintf(reportStr, "bg subtraction and blob detection\npress ' ' to capture bg\nthreshold %i (press: +/-)\nnum blobs found %i \n\n1,2,3,4 to adjust warping points\n(any other key to stop adjusting)", threshold, contourFinder.nBlobs);
	ofDrawBitmapString(reportStr, 20, 600);

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	
	bAdjustingPoint = false;
	whichPointAdjusting = 0;
	
	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
		case '1':
			bAdjustingPoint = true;
			whichPointAdjusting = 0;
			break;
		case '2':
			bAdjustingPoint = true;
			whichPointAdjusting = 1;
			break;
		case '3':
			bAdjustingPoint = true;
			whichPointAdjusting = 2;
			break;
		case '4':
			bAdjustingPoint = true;
			whichPointAdjusting = 3;
			break;
		
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
	if (bAdjustingPoint){
		srcPts[whichPointAdjusting].set(x-20, y-20);
	}
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

