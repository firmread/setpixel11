#include "testApp.h"



bool energyIsLow(tracker t){
	return  ((t.energy < 0.1) && (t.nFramesAlive > 3));
}


//--------------------------------------------------------------
void testApp::setup(){	 
	
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);

        
    colorImg.allocate(320,240);
	grayImage.allocate(320,240);

	
	panel.setup("cv settings", 720, 0, 300, 748);
	panel.addPanel("control", 1, false);
	
	panel.setWhichPanel("control");
	panel.setWhichColumn(0);
	panel.addSlider("scale haar ", "SCALEHAAR", 1.2, 1, 3.0, false);
	
	
	// load the correct xml file from the bin/data/haarXML/ folder
	
	haarFinder.setup("haarXML/haarcascade_frontalface_default.xml");

	
	for (int i = 0; i < 3; i++){
		maskImage[i].loadImage("mask" + ofToString(i) + ".png");
	}
	
	ofBackground(0,0,0);
}

//--------------------------------------------------------------
void testApp::update(){
	
	
    
	panel.update();
	
	float scaleHaar = panel.getValueF("SCALEHAAR");
	haarFinder.setScaleHaar(scaleHaar);
	
	bool bNewFrame = false;
	vidGrabber.grabFrame();
	bNewFrame = vidGrabber.isFrameNew();

	if (bNewFrame){
		colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
        grayImage = colorImg;
		haarFinder.findHaarObjects(grayImage);
	}
	
	// -------------------------------------------------
	
	// let's track these blobs !
	// a) assume all trackers are *not* found this frame. 
	
	for (int i = 0; i < trackerObjects.size(); i++){
		trackerObjects[i].bFoundThisFrame = false;
	}
	
	// b) for all blobs this frame, let's see if we can match them to the trackers.  
	
	int nBlobsFoundThisFrame = haarFinder.blobs.size();
	
	// assume that none have been found:
	bool bAmIFoundThisFrame[nBlobsFoundThisFrame];
	
	if (nBlobsFoundThisFrame > 0){
		
		
		for (int i = 0; i < nBlobsFoundThisFrame; i++){
			bAmIFoundThisFrame[i] = false;
		}
		
		// now, look through every tracker, and see how far away they are from this blob.
		// find the minimum distance, and see if this is reasonable. 
		
		for (int i = 0; i < nBlobsFoundThisFrame; i++){
			
			float	minDistance = 100000;
			int		minIndex	= -1;
			
			for (int j = 0; j < trackerObjects.size(); j++){
				if (trackerObjects[j].bFoundThisFrame == false){
					
					float dx = trackerObjects[j].pos.x - haarFinder.blobs[i].centroid.x;
					float dy = trackerObjects[j].pos.y - haarFinder.blobs[i].centroid.y;
					float distance = sqrt(dx*dx + dy*dy);
					if (distance < minDistance){
						minDistance = distance;
						minIndex = j;
					}
				}
			}
			
			if (minIndex != -1 && minDistance < 100){		// 100 = just a guess.
				trackerObjects[minIndex].pos.x = haarFinder.blobs[i].centroid.x;
				trackerObjects[minIndex].pos.y = haarFinder.blobs[i].centroid.y;
				
				trackerObjects[minIndex].width = haarFinder.blobs[i].boundingRect.width;
				
				trackerObjects[minIndex].widthSmooth = 0.98f * trackerObjects[minIndex].widthSmooth +	
														0.02f * trackerObjects[minIndex].width;
				
				
				trackerObjects[minIndex].posSmooth.x = 0.9f * trackerObjects[minIndex].posSmooth.x + 
														0.1 * trackerObjects[minIndex].pos.x;
				trackerObjects[minIndex].posSmooth.y = 0.9f * trackerObjects[minIndex].posSmooth.y + 
														0.1 * trackerObjects[minIndex].pos.y;
				
				
				
				
				trackerObjects[minIndex].energy += 0.1f;
				if (trackerObjects[minIndex].energy > 1) trackerObjects[minIndex].energy = 1;
				
				trackerObjects[minIndex].whoThisFrame = i;
				trackerObjects[minIndex].bFoundThisFrame = true;
				trackerObjects[minIndex].nFramesAlive ++;
				bAmIFoundThisFrame[i] = true;	// we got one !
			}
		}
	}
	
	// c) for all non found blobs, add a tracker. 
	
	if (nBlobsFoundThisFrame > 0){
		for (int i = 0; i < nBlobsFoundThisFrame; i++){
			if (bAmIFoundThisFrame[i] == false){
				
				tracker temp;
				
				temp.energy = 0;
				
				temp.pos = haarFinder.blobs[i].centroid;
				temp.posSmooth = temp.pos;
				temp.width = haarFinder.blobs[i].boundingRect.width;
				temp.widthSmooth  = temp.width;
				temp.nFramesAlive = 0;
				temp.whoThisFrame = i;
				temp.bFoundThisFrame = true;
				temp.id = idCount;
				trackerObjects.push_back(temp);
				idCount ++;
			}
		}
	}
	
	// d) fade out non found blobs, kill ones that go below a certain value
	// remove_if sorts to the end via a boolean value, 
	// http://en.wikipedia.org/wiki/Erase-remove_idiom
	
	for (int i = 0; i < trackerObjects.size(); i++){
		if(trackerObjects[i].bFoundThisFrame == false){
			 trackerObjects[i].nFramesAlive++;
			 trackerObjects[i].energy *= 0.95f;	
		}
	}
			 
	trackerObjects.erase( remove_if(trackerObjects.begin(), trackerObjects.end(), energyIsLow), trackerObjects.end() );
	
	
	
}

//--------------------------------------------------------------
void testApp::draw(){

	// draw the incoming & the grayscale
	ofSetColor(0xffffff);
	colorImg.draw(20,20);	
	grayImage.draw(360,20);
	
	// how many matches did you find?
	int numMatches = haarFinder.blobs.size();
	
	
	ofPushStyle();
	
	ofSetRectMode(OF_RECTMODE_CENTER);
	
	// drawing the matches
	glPushMatrix();
	glTranslatef(20, 20, 0);
	for(int i = 0; i < trackerObjects.size(); i++){
		
		
		float cx = trackerObjects[i].posSmooth.x;
		float cy = trackerObjects[i].posSmooth.y;
		
		
		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255, trackerObjects[i].energy * 255);
		
		float width = trackerObjects[i].width;
		
		
		maskImage[CLAMP(trackerObjects[i].id % 3,0,2)].draw(cx,cy,width,width);
	}
	glPopMatrix();
	
	
	ofPopStyle();
	
	panel.draw();
	
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	switch (key){
		case 's':
			vidGrabber.videoSettings();
		break;
	}
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
void testApp::mouseReleased(){
	panel.mouseReleased();
}

