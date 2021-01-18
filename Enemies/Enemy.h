#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
//#include"..\Battle.h"
class Battle;
class GUI;
// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:
	const int ID;         //Each enemy has a unique ID (sequence number)
	const int ArrvTime;	//arrival time (time it starts to join battle)
	ENMY_STATUS status;	    //status of the enemy (inactive, inactive, frosted, killed)
							// note that there is no status for active reloading to keep things 
							//simple i included two data memebrs to handle this reload_time and counter

	int Distance;	//Horizontal distance between enemy & the tower of its region
					//Always positive (ranges from 2 to 60)

	double Health;	//Enemy health
	double original_health;
	// added data members not orignally there
	int type;
	int speed; // every enemy has a speed that moves with it
	int power; // every enemy has a power
	int reload_time; //every enemy has a reload time between each step
	int reload_counter;// handled by the act function
	int first_shot; // indicates the the time step that the the enemy was first shot at 
	int killedTime; //indicates the time step the enemy died in
				// this last w data members will be used to calculate FD,KD,LT (chech the project documentation)
	bool IsShoot;
	bool isdead;
	int frost_time_steps;
	int frost_counter;

	//
	// TODO: Add More Data Members As Needed
	//

public:
	Enemy(int id, int arrTime, int d = MaxDistance);//maxdist=60
	Enemy(int id, int type, int arr, int health, int power, int rld, int spd);
	virtual ~Enemy();
	// no need for a setter for the arrival time or id there is no default constructor they must be initialized when an object is creted 
	int Enemy::GetID() const;
	ENMY_STATUS GetStatus() const;
	void SetStatus(ENMY_STATUS);
	void DecrementDist();
	void SetDistance(int);// changes the distance after each time step
	int GetDistance() const;
	int GetArrvTime() const;
	double gethealth() const; // used by the battle to check if the enemu is dead or not then calls the set status(killed)
	void sethealth(double);	// changes the health of a enemy
	int getpower()const;
	void setpower(int);
	int getspeed()const;// not sure i will neef this or not 
	void setspeed(int);	// needed to change the speed when health is below 1/2
	void set_reloadtime(int);
	int get_reload();	//not sure i will need it or not
	int get_reloadcounter()const;
	void decreloadcounter();
	void set_frost(int);//sets the amount to time steps the enemy will be frosted
	int get_frost();	//return the amount of time the enemy will be frosted in(used for the periority queue freezed)
	int get_frost_counter();//not sure i will need this
	void setfrostcounter(int);//sets the frost count
	void set_firstshoot(int);// sets the firstshoot data member
	int get_firstshoot() const;// gets the value of the time step the enemy was shoot in
	void set_killtime(int);// sets the killed  data member
	int get_killtime() const;// gets the value of the time step the enemy was killed in
	int calculateFD(int arrive, int first_shoot);// returns the FD
	int calculateKD(int kill, int first_shoot);// returns the KD
												 // in the battle class we can use this two function to calculate LT
	double getOriginalHealth() const;

	bool getisshoot();
	void setisshoot(int timestep);
	void setisdead(int timestep);
	bool getisdead();
	int gettype() const;

	// Virtual Functions: ----------------

	virtual void Move(Battle*) = 0;	//All enemies can move
	virtual void Act(Battle*) = 0;	//Acting means fighting or healing
	virtual int GETPERIORITY() = 0;//this is used for fighters to load them in the priority Queue

	//
	// TODO: Add More Member Functions As Needed
	//
};

