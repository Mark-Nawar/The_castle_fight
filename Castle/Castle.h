#pragma once
#include "..\Defs.h"
class Castle
{
	double Health;
	int freeze_max;
	int power;
	int max_attack;
	int current_freezed_value;
	bool frosted;


	//
	// TODO: Add More Data Members As Needed
	//

public:

	void SetHealth(double h);
	double GetHealth() const;
	void setpower(int);
	int getpower()

	//
	// TODO: Add More Member Functions As Needed
	//

};

