#pragma once
#include"Enemies/Enemy.h"
#include "Generic_DS\Queue.h"
#include "PQueue.h"
#include"Battle.h"
class Healer : public Enemy
{
	int dir;//a flag indiacting the direction of motion towards_the_castle(1) or away_from_caslte(0)
			//initially towards the castle
public:
	Healer(int id, int arrTime, int d = MaxDistance);
	Healer(int id, int type, int arr, int health, int power, int rld, int spd);
	void Act(Battle*);
	void Move(Battle*);
	int GETPERIORITY();
};

