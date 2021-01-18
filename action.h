#pragma once
#include "Defs.h"
#include "GUI\GUI.h"
class Battle; //forward class declaration

class action
{
protected:
	Battle* pManager;	//the project manager is resposnible for 
public:

	action(Battle*& pApp); 	//constructor


	//Execute action pure virtual as the code depends on the action type (silent/stepbystep/interactive)
	virtual void Execute() = 0;


};




