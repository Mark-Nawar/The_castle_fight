#include "Battle.h"
#include "action.h"
#include "stepbystep.h"
#include "silentmode.h"
#include "interactive.h"
#include <time.h>
#include<fstream>
#include <iostream>

Battle::Battle()
{
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	DemoListCount = 0;
	CurrentTimeStep = 0;
	pGUI = NULL;
	//BCastle = new Castle();
}

//void Battle::setcastle(Castle& C)
//{
//	BCastle = C;
//}
Enemy* Battle::GetCurrentEnemy()
{
	return currentenemy;
}
void Battle::SetCurrentEnemy(Enemy* e)
{
	currentenemy = e;
}
void Battle::AddtoDemoList(Enemy* Ptr)
{
	DemoList[DemoListCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It just enqueue a pointer that is already allocated into the queue
}
GUI* Battle::getgui()
{
	return pGUI;
}

Castle*& Battle::GetCastle()
{
	return BCastle;
}

Queue<Enemy*> Battle::getactivefreezers()
{
	return Active_Freezers;
}

PQueue<Enemy*> Battle::getavtivefighters()
{
	return Active_fighters;
}

stack<Enemy*> Battle::gethealers()
{
	return Activ_Healers;
}
PQueue<Enemy*> Battle::getfrosted()
{
	return Frozen_list;
}
Queue<Enemy*> Battle::getkilled()
{
	return Killed_list;
}



void Battle::checkcastlefrosted()
{
	if (BCastle->GetFrosted())
		BCastle->SetFrosted(false);
	return;
}
int Battle::getcurrentstep()
{
	return CurrentTimeStep;
}

bool Battle::castlelose()
{
	return BCastle->GetHealth() <= 0;
}
bool Battle::enemylose()
{
	return KilledCount == EnemyCount;
}
bool Battle::battleDraw()
{
	if (EnemyCount==0 && BCastle->GetHealth()==0)
		return true;
	return false;
}
bool Battle::silent_mode()
{
	this->ActivateEnemies();
	this->decfrosted();
	this->moveactv();
	if (CurrentTimeStep % 2 == 0)
	{
		this->CastleAttack();
		this->enemyact();
	}
	else
	{
		this->enemyact();
		this->CastleAttack();
	}
	this->AddAllListsToDrawingList();
	if (castlelose() || enemylose() || battleDraw())
		return false;
	CurrentTimeStep++;
	return true;
}
bool Battle::stepbystep_and_interactive_battle()
{

	this->ActivateEnemies();
	this->moveactv();
	this->decfrosted();
	if (CurrentTimeStep % 2 == 0)
	{
		this->CastleAttack();
		this->enemyact();
	}
	else
	{
		this->enemyact();
		this->CastleAttack();
	}
	this->AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep);
	pGUI->UPDATEDATA(BCastle->GetFrosted(),BCastle->GetHealth(),activef,activefr,activeh,frostedF,frostedFr,frostedH,killedF,killedFr,killedH);
	if (castlelose() || enemylose() || battleDraw())
		return false;
	CurrentTimeStep++;
	return true;

}
void Battle::ActivateEnemies()
{
	Enemy* tmp;
	if (Q_Inactive.peekFront(tmp))
	{
		while (tmp->GetArrvTime() == CurrentTimeStep && Q_Inactive.dequeue(tmp))
		{
			tmp->SetStatus(ACTV);
			// conditions to check what type of fighter is this by dynamic cast;
			if (dynamic_cast<Fighter*>(tmp)) {

				int p = tmp->GETPERIORITY();
				Active_fighters.enPQueue(tmp, tmp->GETPERIORITY());//get prioority when done
			}
			//add to the active fighters list Pqueue after calculating its periority 
			else if (dynamic_cast<Healer*>(tmp))
				Activ_Healers.push(tmp);
			//add to the stack of healers (they come from the inactive already sorted so the stack will besorted as well
			else // must be freezer
				Active_Freezers.enqueue(tmp);
			// add to the queue of active freezers
			Q_Inactive.peekFront(tmp);
		}
	}
	// after the while loop all the enemies on the tip of the inactive queue will be uploaded to thir suitble lists

}

void Battle::moveactv()
{
	// move all the enemies in all the queues by calling their function move
	//start with the actv fighters  dequeue every fighter and after the end reinsert in after calculating its new periority
	Queue<Enemy*>tmpq;
	stack<Enemy*>tmps;
	Enemy* tmp;
	while (Active_fighters.dePQueue(tmp))
	{
		tmp->Move(this);
		tmpq.enqueue(tmp);
	}
	while (tmpq.dequeue(tmp))
		Active_fighters.enPQueue(tmp, tmp->GETPERIORITY());// add prio

	while (Active_Freezers.dequeue(tmp))
	{
		tmp->Move(this);
		tmpq.enqueue(tmp);
	}
	while (tmpq.dequeue(tmp))
		Active_Freezers.enqueue(tmp);
	while (Activ_Healers.pop(tmp))
	{
		tmp->Move(this);
		tmps.push(tmp);
	}
	while (tmps.pop(tmp))
		Activ_Healers.push(tmp);

}
void Battle::decfrosted()
{
	Queue<Enemy*>tmpq;
	Enemy* tmp;
	while (Frozen_list.dePQueue(tmp))
	{
		tmp->set_frost(tmp->get_frost() - 1);
		if (tmp->get_frost() == 0)
		{
			tmp->SetStatus(ACTV);
			if (dynamic_cast<Fighter*>(tmp))
				Active_fighters.enPQueue(tmp, tmp->GETPERIORITY());
			else if (dynamic_cast<Healer*>(tmp))
				Activ_Healers.push(tmp);
			else
				Active_Freezers.enqueue(tmp);
		}
		else
			tmpq.enqueue(tmp);
	}
	while (tmpq.dequeue(tmp))
		Frozen_list.enPQueue(tmp, (100 / tmp->get_frost()));
}
void Battle::CastleAttack()
{
	if (BCastle->GetFrosted())
	{
		BCastle->SetFrosted(false);
		BCastle->SetCurrFreeze(0);
		return;
	}
	srand(time(NULL));
	int max = BCastle->GetMaxEnemies();
	int count = 0;
	Enemy* tmp;
	stack<Enemy*>tmps;
	Queue<Enemy*> tmpq;
	while (count < max && Active_fighters.dePQueue(tmp))
	{
		this->SetCurrentEnemy(tmp);
		BCastle->Attack(this);
		if (tmp->GetStatus() == FRST)
			Frozen_list.enPQueue(tmp, (100 / (tmp->get_frost() + 1)));
		else if (tmp->GetStatus() == KILD)
			Killed_list.enqueue(tmp);
		else
			tmpq.enqueue(tmp);
		count++;
	}
	while (tmpq.dequeue(tmp))
		Active_fighters.enPQueue(tmp, tmp->GETPERIORITY());

	while (count < max && Activ_Healers.pop(tmp))
	{
		this->SetCurrentEnemy(tmp);
		BCastle->Attack(this);
		if (tmp->GetStatus() == FRST)
			Frozen_list.enPQueue(tmp, (100 / (tmp->get_frost() + 1)));
		else if (tmp->GetStatus() == KILD)
			Killed_list.enqueue(tmp);
		else
			tmps.push(tmp);
		count++;
	}
	while (tmps.pop(tmp))
		Activ_Healers.push(tmp);

	while (count < max && Active_Freezers.dequeue(tmp))
	{
		this->SetCurrentEnemy(tmp);
		BCastle->Attack(this);
		if (tmp->GetStatus() == FRST)
			Frozen_list.enPQueue(tmp, (100 / (tmp->get_frost() + 1)));
		else if (tmp->GetStatus() == KILD)
			Killed_list.enqueue(tmp);
		else
			tmpq.enqueue(tmp);
		count++;
	}
	while (tmpq.dequeue(tmp))
		Active_Freezers.enqueue(tmp);
}
void Battle::enemyact()
{
	Queue<Enemy*>tmpq;
	stack<Enemy*>tmps;
	Enemy* tmp;
	Enemy* tmpF;
	while (Active_fighters.dePQueue(tmp))
	{
		tmp->Act(this);
		tmpq.enqueue(tmp);
	}
	while (tmpq.dequeue(tmp))
		Active_fighters.enPQueue(tmp, tmp->GETPERIORITY());// add prio

	while (Active_Freezers.dequeue(tmp))
	{
		tmp->Act(this);
		tmpq.enqueue(tmp);
	}
	while (tmpq.dequeue(tmp))
		Active_Freezers.enqueue(tmp);



	while (Active_Freezers.dequeue(tmp))
	{
		tmp->Act(this);
		tmpq.enqueue(tmp);
	}
	while (tmpq.dequeue(tmp))
		Active_Freezers.enqueue(tmp);


	while (Activ_Healers.pop(tmp))
	{
		while (Active_fighters.dePQueue(tmpF))
		{
			this->SetCurrentEnemy(tmpF);
			tmp->Act(this);
			tmpq.enqueue(tmpF);
		}
		while (tmpq.dequeue(tmpF))
			Active_fighters.enPQueue(tmpF, tmpF->GETPERIORITY());
		while (Active_Freezers.dequeue(tmpF))
		{
			this->SetCurrentEnemy(tmpF);
			tmp->Act(this);
			tmpq.enqueue(tmpF);
		}
		while (tmpq.dequeue(tmpF))
			Active_Freezers.enqueue(tmpF);
		tmps.push(tmp);
	}
	while (tmps.pop(tmp))
		Activ_Healers.push(tmp);

}
void Battle::AddAllListsToDrawingList()
{
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy* const* EnemyList = Q_Inactive.toArray(InactiveCount);
	for (int i = 0; i < InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyList[i]);

	//the active  that fills the activ fighters,healers,feezers in the drawing list
	int activefighterscount;
	Enemy* const* actvfighter = Active_fighters.toArray(activefighterscount);
	for (int i = 0; i < activefighterscount; i++)
		pGUI->AddToDrawingList(actvfighter[i]);

	int activehealers;//healers active from stac edit the next line
	Enemy* const* actvhealers = Activ_Healers.Toarray(activehealers); // to do active healer in stack
	for (int i = 0; i < activehealers; i++)
		pGUI->AddToDrawingList(actvhealers[i]);

	int activefreezers;//freezers that are active so edit the next line
	Enemy* const* actvfreezer = Active_Freezers.toArray(activefreezers);
	for (int i = 0; i < activefreezers; i++)
		pGUI->AddToDrawingList(actvfreezer[i]);
	ActiveCount = activefighterscount + activehealers + activefreezers;
	this->activef = activefighterscount;
	this->activefr = activefreezers;
	this->activeh = activehealers;
	//// fill the killed enemy edit the next line
	int frostedenemies;
	int FrostedF = 0;
	int FrostedFr = 0;
	int FrostedH = 0;
	Enemy* const* frozen = Frozen_list.toArray(frostedenemies);
	for (int i = 0; i < frostedenemies; i++)
	{
		if (dynamic_cast<Fighter*>(frozen[i]))
			FrostedF++;
		else if (dynamic_cast<Healer*>(frozen[i]))
			FrostedH++;
		else
			FrostedFr++;
		pGUI->AddToDrawingList(frozen[i]);
	}
	FrostedCount = frostedenemies;
	this->frostedF = FrostedF;
	this->frostedFr = FrostedFr;
	this->frostedH = FrostedH;
	/////fill the killed enemies to the drawing list edit when ADTs are done
	int killedenemies;
	int kf = 0;
	int kfr = 0;
	int kh = 0;
	Enemy* const* killed_list = Killed_list.toArray(killedenemies);
	for (int i = 0; i < killedenemies; i++)
	{
		if (dynamic_cast<Fighter*>(killed_list[i]))
			kf++;
		else if (dynamic_cast<Healer*>(killed_list[i]))
			kh++;
		else
			kfr++;
		pGUI->AddToDrawingList(killed_list[i]);
	}
	KilledCount = killedenemies;
	this->killedF = kf;
	this->killedH = kh;
	this->killedFr = kfr;
	//filling of all the enemies are done they are ready to be drawn on the screen 
	// recaalling this function should redo the same thing with the enemies status updated
	/*for(int i=0; i<DemoListCount; i++)
		pGUI->AddToDrawingList(DemoList[i]);*/// for the sake of the demo
}


void Battle::LOAD()
{
	pGUI->PrintMessage("ENTER THE NAME OF THE TXT FILE (INCLUDE THE .txt )");
	string fileName = pGUI->GetString();
	ifstream InFile;
	InFile.open(fileName, ios::in);
	while (!(InFile.is_open()))//check if the file opens or not if not it keeps asking for a valid name.
	{
		pGUI->PrintMessage("invalid file name retry");
		fileName = pGUI->GetString();
		InFile.open(fileName, ios::in);
	}

	double CH;
	int N, CP;
	InFile >> CH >> N >> CP;
	BCastle = new Castle(CH, N, CP);
	int totalE;
	InFile >> totalE;
	EnemyCount = totalE;
	int ID, TYP, AT, POW, RLD, SPD;
	double H;
	for (int i = 0; i < totalE; i++)//as we don't reach end of file continue working
	{
		InFile >> ID >> TYP >> AT >> H >> POW >> RLD >> SPD;
		if (TYP == 0)
		{
			Enemy* e = new Fighter(ID, TYP, AT, H, POW, RLD, SPD);
			Q_Inactive.enqueue(e);
		}
		else if (TYP == 1)
		{
			Enemy* e1 = new Healer(ID, TYP, AT, H, POW, RLD, SPD);
			Q_Inactive.enqueue(e1);
		}
		else if (TYP == 2)
		{
			Enemy* e2 = new Freezer(ID, TYP, AT, H, POW, RLD, SPD);
			Q_Inactive.enqueue(e2);

		}
	}
	InFile.close();
	return;
}

void Battle::Save()
{
	ofstream output;
	output.open("output.txt", ios::out);
	if (castlelose())
		output << "Castle Destroyed, we lost" << endl;
	else if (enemylose())
		output << "Mighty Castle,All the enemies are killed, Game Won" << endl;
	else
		output << "The Game is Draw" << endl;
	output << "KTS	   ID	    FD	    KD	    LT" << endl;
	Enemy* tmpe;
	/*which means that the enemy identified by sequence number ID is killed at time step KTSand
	 its first - shot delay is FD and kill delay is KD and total enemy lifetime is LT.
	The output lines should be sorted by KTS in ascending order.*/
	int totFD = 0;
	int totKD = 0;
	for (int i = 0; i < KilledCount; i++)
	{
		Killed_list.dequeue(tmpe);
		int FD = tmpe->get_firstshoot() - tmpe->GetArrvTime();
		int KD = tmpe->get_killtime() - tmpe->get_firstshoot();
		totFD += FD;
		totKD += KD;
		output << tmpe->get_killtime() << "\t" << tmpe->GetID() << "\t" << FD << "\t" << KD << "\t" << FD + KD << endl;
	}
	output << "The Castle Final Health" << "\t" << BCastle->GetHealth() << endl;
	if (enemylose())
	{
		output << "Mighty Castle,All the enemies are killed, Game Won" << endl;
		output << "The Total number of enemies" << "\t" << EnemyCount << endl;
		output << "The Average First Shot Delay:" << (double)totFD / EnemyCount << endl;
		output << "The Average Kill Delay :" << (double)totKD / EnemyCount << endl;
	}
	else
	{
		output << "Castle Destroyed, we lost" << endl;
		output << "Number of killed enemies:" << KilledCount << endl;
		output << "Number of alive enemies:" << ActiveCount << endl; //both should sum up to the total enemies count
		if (KilledCount != 0)
		{
			output << "The Average First Shot Delay:" << (double)totFD / KilledCount << endl;
			output << "The Average Kill Delay :" << (double)totKD / KilledCount << endl;
		}
		else
		{
			output << "The Average First Shot Delay:" << 0 << endl;
			output << "The Average Kill Delay :" << 0 << endl;
		}
	}
	pGUI->ResetDrawingList();
	output.close();
}
















//void Battle::castleattack()
//{
//	srand(time(NULL));
//	Enemy* E;
//	int count = 0;
//	PQueue<Enemy*>tempfighters;
//	stack<Enemy*>temphealers;
//	Queue<Enemy*> tempfreezers;
//	while (count < BCastle->GetMaxEnemies() && Active_fighters.dePQueue(E))// attacking fighterss
//	{
//		BCastle->setattacktype((rand() % 10) >= 2);
//		if (!E->getisshoot())
//			E->set_firstshoot(CurrentTimeStep);
//		if (BCastle->getattacktype())// if the castle attacked fighters using bullets
//		{
//			int Dce = (20 / E->GetDistance()) * BCastle->GetCastlePower() * (1);
//			double EnemyHealthO = E->gethealth();
//			E->sethealth(EnemyHealthO - Dce);
//			if (E->gethealth() <= 0)// enqueue in the killed list
//			{
//				E->SetStatus(KILD);
//				E->set_killtime(CurrentTimeStep);
//				Killed_list.enqueue(E);
//			}
//			else // enqueue in the tempfighters queue but dont forget to return this queue to the original one ACTIVE FIGHTERS
//			{
//				tempfighters.enPQueue(E, E->GETPERIORITY());
//			}
//		}
//		else //if the castle attacked fighters using ice
//		{
//			int F = (int)(((1 / E->GetDistance()) * BCastle->GetCastlePower() * E->gethealth()) / 3) + (1);
//			E->SetStatus(FRST);
//			E->set_frost(F);
//			Frozen_list.enPQueue(E, (100 / (F + 1)));
//
//		}
//		count++;
//	}
//
//	while (tempfighters.dePQueue(E))// return the tempfighters to the active fighters
//	{
//		Active_fighters.enPQueue(E, E->GETPERIORITY());
//	}
//	/////////////////////////////////////////////////////////////////////////////////////////////////////
//	////////////////////THINK Should we attack frozen enemies
//	////////////////////////////////////////////////////////////////////////////////////////////////////
//	while (count < BCastle->GetMaxEnemies() && Activ_Healers.pop(E) )//Attacking Healers
//	{
//		BCastle->setattacktype(((rand() % 10) >= 2));
//		if (!E->getisshoot())
//			E->set_firstshoot(CurrentTimeStep);
//		if (BCastle->getattacktype())// if castle attack the healers using bullets
//		{
//			int Dce = (1 / E->GetDistance()) * BCastle->GetCastlePower() * (0.5);
//			double HealerHealthO = E->gethealth();
//			E->sethealth(HealerHealthO - Dce);
//			if (E->gethealth() <= 0) // if the healer is killed, then healer is enqueued in the killed list
//			{
//				E->SetStatus(KILD);
//				E->set_killtime(CurrentTimeStep);
//				Killed_list.enqueue(E);
//
//			}
//			else // if the healer isnt dead then it is pushed in a temphealer stack
//			{
//				temphealers.push(E);
//
//			}
//		}
//		else // if the castle attacks the healer using ice
//		{
//			int F = (int)(((1 / E->GetDistance()) * BCastle->GetCastlePower() * E->gethealth()) / 3) + (2);
//			E->SetStatus(FRST);
//			E->set_frost(F);
//			Frozen_list.enPQueue(E, (100 / (F + 1)));
//
//		}
//		count++;
//
//	}
//	while (temphealers.pop(E))
//	{
//		Activ_Healers.push(E);
//	}
//
//	while (count < BCastle->GetMaxEnemies() && Active_Freezers.dequeue(E))//attacking freezers
//	{
//		BCastle->setattacktype(((rand() % 10) >= 2));
//		if (!E->getisshoot())
//			E->set_firstshoot(CurrentTimeStep);
//		if (BCastle->getattacktype())// if castle attack the freezers using bullets
//		{
//			double Dce = (20 / E->GetDistance()) * BCastle->GetCastlePower() * (1);
//			double EnemyHealthO = E->gethealth();
//			E->sethealth(EnemyHealthO - Dce);
//			if (E->gethealth() <= 0) //if freezer is killed then it is enqueued in the killed list
//			{
//				E->SetStatus(KILD);
//				E->set_killtime(CurrentTimeStep);
//				Killed_list.enqueue(E);
//
//			}
//			else //if the freezer isnt killed, then it is enqueued in the tempfreezers
//			{
//				tempfreezers.enqueue(E);
//			}
//		}
//
//		else //if the castle attacks the freezers using ice, then it is enqueued in the frosted list
//		{
//			int F = (int)(((1 / E->GetDistance()) * BCastle->GetCastlePower() * E->gethealth()) / 3) + (1);
//			E->SetStatus(FRST);
//			E->set_frost(F);
//			Frozen_list.enPQueue(E, (100 / (F + 1)));
//		}
//		count++;
//	}
//	while (tempfreezers.dequeue(E)) //returns the tempfreezer queue to the original queue Active Freezers
//	{
//		Active_Freezers.enqueue(E);
//	}
//	//BCastle->Attack(this);
//}





void Battle::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
	action* actiontype = nullptr;

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		actiontype = new interactive(this);
		break;
	case MODE_STEP:
		actiontype = new stepbystep(this);
		break;
	case MODE_SLNT:
		actiontype = new silentmode(this);
		break;
	case MODE_DEMO:
		Just_A_Demo();

	}
	if (actiontype)
	{
		actiontype->Execute();
		delete actiontype;
		actiontype = nullptr;
	}

	delete pGUI;

}


//This is just a demo function for project introductory phase
//It should be removed in phases 1&2
void Battle::Just_A_Demo()
{

	pGUI->PrintMessage("Just a Demo. Enter Enemies Count(next phases should read I/P filename):");
	EnemyCount = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->PrintMessage("Generating Enemies randomly... In next phases, Enemies should be loaded from a file...CLICK to continue");
	pGUI->waitForClick();

	CurrentTimeStep = 0;
	//
	// THIS IS JUST A DEMO Function
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	//

	srand(time(NULL));
	int Enemy_id = 0;
	int ArrivalTime = 1;
	Enemy* pE = NULL;
	//Create Random enemies and add them all to inactive queue
	for (int i = 0; i < EnemyCount; i++)
	{
		ArrivalTime += (rand() % 3);	//Randomize arrival time
		//pE = new Enemy(++Enemy_id,ArrivalTime);
		pE->SetStatus(INAC); //initiall all enemies are inactive
		Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
	}

	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();

	while (KilledCount < EnemyCount)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();

		Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes only)

		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep);
		Sleep(250);
	}
}


//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface


//check the inactive list and activate all enemies that has arrived
//void Battle::ActivateEnemies()
//{
//	Enemy *pE;
//	while( Q_Inactive.peekFront(pE) )	//as long as there are more inactive enemies
//	{
//		if(pE->GetArrvTime() > CurrentTimeStep )	//no more arrivals at current time
//			return;
//				
//		Q_Inactive.dequeue(pE);	//remove enemy from the queue
//		pE->SetStatus(ACTV);	//make status active
//		AddtoDemoList(pE);		//move it to demo list (for demo purposes)
//	}
//}
// the real activate



//Randomly update enemies distance/status (for demo purposes)
void Battle::Demo_UpdateEnemies()
{
	Enemy* pE;
	int Prop;
	//Freeze, activate, and kill propablities (for sake of demo)
	int FreezProp = 5, ActvProp = 10, KillProp = 1;
	srand(time(0));
	for (int i = 0; i < DemoListCount; i++)
	{
		pE = DemoList[i];
		switch (pE->GetStatus())
		{
		case ACTV:
			pE->DecrementDist();	//move the enemy towards the castle
			Prop = rand() % 100;
			if (Prop < FreezProp)		//with Freeze propablity, change some active enemies to be frosted
			{
				pE->SetStatus(FRST);
				ActiveCount--;
				FrostedCount++;
			}
			else	if (Prop < (FreezProp + KillProp))	//with kill propablity, kill some active enemies
			{
				pE->SetStatus(KILD);
				ActiveCount--;
				KilledCount++;
			}

			break;
		case FRST:
			Prop = rand() % 100;
			if (Prop < ActvProp)			//with activation propablity, change restore some frosted enemies to be active again
			{
				pE->SetStatus(ACTV);
				ActiveCount++;
				FrostedCount--;
			}

			else	if (Prop < (ActvProp + KillProp))			//with kill propablity, kill some frosted enemies
			{
				pE->SetStatus(KILD);
				FrostedCount--;
				KilledCount++;
			}

			break;
		}
	}


	//////////RETURNS/////////////////
}
