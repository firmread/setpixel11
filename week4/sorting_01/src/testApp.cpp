#include "testApp.h"


// this is the "comparison" function
int compare( const void *a,  const void *b){			
	
	// the const void means -- this function doesn't have a "set" type -- 
	// it's very C style. 
	
	// we first (step1) convert a and b to float points
	// (step2) we dereference to get the values held by a and b
	// I know this is crazy !!  but it works and is fast !! 
	// for those in the know, STL vector < > has sorting functionality too
	// I will show you that at some point....
	// kk.
	
	float *aPtr = ( float *)a;	// (step1) casting pointer types to be of the type float *
	float *bPtr = ( float *)b;
	float valuea = *aPtr;		// (step2) get the value out of ptr a and b...
	float valueb = *bPtr;
	if (valuea > valueb) return 1;
	else return -1;
}


//--------------------------------------------------------------
void testApp::setup(){

	
	myValues[0] = 100;
	myValues[1] = 20;
	myValues[2] = 44;
	myValues[3] = 123;
	myValues[4] = 52;
	myValues[5] = 10;
	myValues[6] = 299;
	
	qsort (myValues, 7, sizeof(float), compare);
	
	for (int i = 0; i < 7; i++){
		printf("myValues %f \n", myValues[i]);
		
	}
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

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

