#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	
	ofBackground(255,255,255);
}

//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	//glTranslatef(<#GLfloat x#>, <#GLfloat y#>, <#GLfloat z#>);
	//glRotatef(<#GLfloat angle#>, <#GLfloat x#>, <#GLfloat y#>, <#GLfloat z#>);
	//glScalef(<#GLfloat x#>, <#GLfloat y#>, <#GLfloat z#>);
	
	
	ofSetColor(0, 0, 0);
	ofRect(10, 10, 100, 100);
	
	
	glPushMatrix();
		
		glTranslatef(200, 0, 0);
		glScalef(2, 1, 0);
		
		ofRect(10, 10, 100, 100);
	
		glPushMatrix();
			glRotatef(PI, 0, 1, 0);
			ofRect(10, 10, 100, 100);
		glPopMatrix();
	
	glPopMatrix();
	
	ofSetColor(255, 0, 0);
	
	ofRect(0, 0, 10, 10);
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

