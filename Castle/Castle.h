#pragma once
#include "..\Defs.h"
#include"..\Battle.h"

class Castle
{
	double Health;
	int attack_type; // the castle can throw bullets of ice this indicates which one 1-bullets 0-ice 
					 // the ratio should be 80 bullets: 20 ice 
	int total_shots;// used to regulate the 20
	// might possibly need to add a data member for the current time step will see tonight
	int MaxNumOfEnemies; //maximum number of enemies the castle can attack at any time step
	int CastlePower; //castle power
	int freeze_max; //frost threshold
	int current_freezed_value; //current frost threshold
	bool frosted;// castle frosted or not
	int HealerDist; // If Castle kills a healer within a "distance" of 5 meters from the castle, it uses healer's tools to recover its health by a percentage of 3 % .
	//bool CastleWin;// bool that sets if the castle won or lost
	int CounttoMax;

public:

	int getcurrentfreezevalue();//getter for frost threshold
	void set_current_freez_value(int);//setter for frost threshold
	Castle();
	Castle(double h, int maxe, int cp);//non-default constructor
	void SetHealth(double h); //a setter for health
	double GetHealth() const;//a getter for health
	int getfreezevalue();
	void SetMaxEnemies(int m); //setter for max enemies a castle can attack at any time step
	int GetMaxEnemies()const;//getter for  max enemies a castle can attack at any time step
	void SetCastlePower(int c);//setter for castle power
	int GetCastlePower() const;//getter for castle power
	int GetHealerDist();//getter for healer distance from castle
	int getcounttomax();
	void setcounttomax(int);
	void SetFrosted(bool t);//setter to frost castle or not
	bool GetFrosted();//getter to frost castle or not
	void SetCurrFreeze(int cf);//setter for current frost threshold
	int GetCurrFreeze();//getter for current frost threshold
	void Attack(Battle*);//Function attack enables the castle to attack its enemies by ice(0) or bullets(1)
	bool CastleWin();// bool to be set to show castle won or not
	~Castle();//destructor
	void setattacktype(int);//setter for attack type
	int getattacktype();//getter for attack type
	//
	// TODO: Add More Member Functions As Needed
	//


};

