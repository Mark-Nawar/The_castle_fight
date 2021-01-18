#pragma once

#include "GUI\GUI.h"
#include"Castle/Castle.h"
//#include"castle.h"
#include "Generic_DS\Queue.h"
#include "PQueue.h"
#include"stack.h"
#include "Enemies\Enemy.h"
#include"Fighter.h"
#include"Healer.h"
#include"Freezer.h"
// it is the controller of the project
class Castle;
class Battle
{
private:
	GUI* pGUI;
	//Castle BCastle;
	Castle *BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	int ActiveCount, FrostedCount, KilledCount;	//no. of enemies (Active, Frosted, killed so far)
	int activef, activefr, activeh;
	int frostedF, frostedFr, frostedH;
	int killedF, killedFr, killedH;
	int CurrentTimeStep;
	int MaxForDraw;
	Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function

	Queue<Enemy*> Q_Inactive;		//Queue of inactive enemies

	PQueue<Enemy*>Active_fighters; // A Periority Queue that conatins the ememies sorted by their danger on the castle
	                               // and accordingly the castle will attack them 
	                               // the enemy will be dequed and then enqued again with the new periority into the Pqueue again
	
	stack<Enemy*>Activ_Healers;   //Then(if N is not exhausted yet), pick healers to attack.A fresh healer who has just joined
		                           //the forces is picked first.This means that healers are picked in the reverse order of their
		                           //arrival(Last - Come - First - Serve)

	Queue<Enemy*>Active_Freezers;  //Finally(if N is not exhausted yet) pick freezers to attack.A freezer that arrived first
		                           //should be attacked first(First - Come - First - Serve).

	PQueue<Enemy*> Frozen_list;  //  Frozen list is a Pri-Q because enemies don't leave frozen list in the same order they
	                             //entered it but after ice melts which is different for each enemy in the list

	Queue<Enemy*>Killed_list;
	Enemy* currentenemy;

	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	//Queue for all enemies in the battle
	int DemoListCount;
	Enemy* DemoList[MaxEnemyCount];	//Important: This is just for demo
	/// ==>


	//
	// TODO: Add More Data Members As Needed
	//

public:
	
	Battle();
	void AddAllListsToDrawingList();		//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
	Castle*& GetCastle();
	//void setcastle(Castle&);
	void RunSimulation();
	void ActivateEnemies();		//check the inactive list and activate all enemies that has arrived


	void AddtoDemoList(Enemy* Ptr);		//Add Enemy to the demo queue of enemies (for demo purposes only)
	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes)

	//////////***************the main Battle Simulation that is called from the classes of actions****************/////////////
	bool stepbystep_and_interactive_battle();
	bool silent_mode();// to inputs as it will not draw anything
	void moveactv();
	void decfrosted();
	void updatestatus();
	void castleattack();
	void CastleAttack();
	void enemyact();
	void checkcastlefrosted();
	int getcurrentstep();
	bool castlelose();
	bool enemylose();
	bool battleDraw();
	GUI* getgui();
	void SetCurrentEnemy(Enemy*);
	Enemy* GetCurrentEnemy();
	PQueue<Enemy*> getavtivefighters();
	Queue<Enemy*> getactivefreezers();
	stack<Enemy*> gethealers();
	Queue<Enemy*> getkilled();
	PQueue<Enemy*> getfrosted();
	

	void LOAD();
	void Save();

	

	
	//
	// TODO: Add More Member Functions As Needed
	//
};

