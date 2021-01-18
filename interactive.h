#pragma once
#include "action.h"
class interactive :
    public action
{
public:
	interactive(Battle*);
	void Execute();
	~interactive();

};
