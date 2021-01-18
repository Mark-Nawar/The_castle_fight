#pragma once
#include "action.h"
class silentmode :
    public action
{
public:
	silentmode(Battle* pApp);
	void Execute();
	~silentmode();
};