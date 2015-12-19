#pragma once

#include "CogApp.h"
#include "CogEngine.h"

#define APP_SPEED 60

namespace Cog {

	void CogApp::InitComponents() {
		Factory* fact = new Factory();
		COGEngine.entityStorage->RegisterComponent(fact);
		COGEngine.nodeStorage->SetRootObject(fact->CreateRoot());
	}

	void CogApp::InitEngine() {
		COGEngine.Init();
	}

void CogApp::setup(){
	// never set vertical sync
	ofSetVerticalSync(false);
	ofSetFrameRate(APP_SPEED);
	ofEnableAntiAliasing();
	// initialize COG engine
	this->InitComponents();
	this->InitEngine();
	
	// initialize time
	absolute = ofGetSystemTime();
	delta = ofGetSystemTime();
}

void CogApp::draw(){
	// drawing loop
	COGEngine.Draw(delta, absolute);
}

void CogApp::update(){
	// update loop
	delta = ofGetSystemTime() - absolute;
	absolute = ofGetSystemTime();

	uint64 semiFixedDelta = (delta < 16) ? 16 : (delta < 32) ? delta : 32;

	COGEngine.Update(semiFixedDelta, absolute);
}

void CogApp::keyPressed(int key){
	COGEngine.environment->OnKeyAction(key, true);
}

void CogApp::keyReleased(int key){
	COGEngine.environment->OnKeyAction(key, false);
}

void CogApp::windowResized(int w, int h){
	COGEngine.environment->OnScreenSizeChanged(w, h);
}



#ifdef WIN32

void CogApp::mouseMoved(int x, int y){

}

void CogApp::mouseDragged(int x, int y, int button){
	COGEngine.environment->OnSingleTouchMotion(x, y, button);

}

void CogApp::mousePressed(int x, int y, int button){
	COGEngine.environment->OnSingleTouchButton(x, y, button, true);
}

void CogApp::mouseReleased(int x, int y, int button){
	COGEngine.environment->OnSingleTouchButton(x, y, button, false);
}

void CogApp::dragEvent(ofDragInfo dragInfo){

}


#else


void CogApp::swipe(ofxAndroidSwipeDir swipeDir, int id){

}

void CogApp::pause(){

}

void CogApp::stop(){

}

void CogApp::resume(){

}

void CogApp::reloadTextures(){

}

bool CogApp::backPressed(){
	return false;
}

void CogApp::okPressed(){

}

void CogApp::cancelPressed(){

}

void CogApp::touchDown(int x, int y, int id){
	COGEngine.environment->OnMultiTouchButton(x, y, id, true);
}

void CogApp::touchMoved(int x, int y, int id){
	COGEngine.environment->OnMultiTouchMotion(x, y, id);
}

void CogApp::touchUp(int x, int y, int id){
	COGEngine.environment->OnMultiTouchButton(x, y, id, false);
}

void CogApp::touchDoubleTap(int x, int y, int id){

}

void CogApp::touchCancelled(int x, int y, int id){

}

#endif

}// namespace