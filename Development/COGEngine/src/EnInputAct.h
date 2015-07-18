#pragma once

#include "Enums.h"

enum InputType{
	KEYBOARD, TOUCH
};

/**
* EnInputAct - entity for input activity
*/
class EnInputAct{
public:
	InputType inputType;
	// pressed key (keyboard only)
	int key;
	// pressed finger (touch input only)
	int buttonId;
	// position (only for mouse and touch events)
	ofVec3f position;

	// handlerId, -1 if there is none
	int handlerId;
	// indicates, if input has just started (only for pointer events)
	// if false, it means that pointer is in motion
	bool started;
	// indicates, if input has ended (e.g. key release)
	bool ended;


	EnInputAct(int keyboardKey) : inputType(InputType::KEYBOARD), key(keyboardKey){
		Construct();
	}

	EnInputAct(int button, ofVec3f pos) : inputType(InputType::TOUCH), buttonId(button), position(pos){
		Construct();
	}

	/*EnInputAct(int touchID, ofVec3f pos) :inputType(InputType::TOUCH), touchId(touchID),  position(pos){
		Construct();
	}*/

	EnInputAct(){
		Construct();
	}

	void Construct(){
		handlerId = -1;
		started = true;
		ended = false;
	}

	// indicates, if input has been handled
	bool IsHandled(){
		return handlerId != -1;
	}

};
