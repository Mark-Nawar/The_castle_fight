#include "Castle.h"
#include <time.h>


void Castle::set_current_freez_value(int freezed_total)
{
	current_freezed_value = freezed_total;
	if (current_freezed_value >= freeze_max)
		frosted = true;
}
int  Castle::getcurrentfreezevalue()
{
	return current_freezed_value;
}

Castle::Castle()
{

}

Castle::Castle(double h, int maxenemies, int cp)
{
	Health = h;
	MaxNumOfEnemies = maxenemies;
	CastlePower = cp;
	freeze_max = 100;
	frosted = false;
	current_freezed_value = 0;
	HealerDist = 5;
}

void Castle::SetHealth(double h)
{
	if (h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Castle::GetHealth() const
{
	return Health;
}

void Castle::SetMaxEnemies(int e)
{
	MaxNumOfEnemies = e;
}

int Castle::GetMaxEnemies()const
{
	return MaxNumOfEnemies;
}

void Castle::SetCastlePower(int cp)
{
	CastlePower = cp;
}

int Castle::GetCastlePower()const
{
	return CastlePower;
}

//void Castle::SetFD()
//{

//}

//int Castle::GetFD()
//{


//}


int Castle::GetHealerDist()
{
	return HealerDist;
}


void Castle::SetCurrFreeze(int cf)
{
	current_freezed_value = cf;

}

int Castle::GetCurrFreeze()
{
	return current_freezed_value;
}

void Castle::SetFrosted(bool t)
{
	frosted = t;
}

bool Castle::GetFrosted()
{
	return frosted;
}
int  Castle::getcounttomax()
{
	return CounttoMax;
}
void Castle::setcounttomax(int mx)
{
	CounttoMax = mx;
}

void Castle::Attack(Battle* b)
{
	Enemy* E;
	E = b->GetCurrentEnemy();
	if (!E->getisshoot())
		E->set_firstshoot(b->getcurrentstep());
	this->setattacktype((rand() % 10) >= 2);
	if (getattacktype())// if the castle attacked fighters using bullets
	{
		int Dce;
		if (E->gettype() == 1)
			Dce = (1 / double(E->GetDistance())) * this->GetCastlePower() * 0.5;
		else
			Dce = (1 / double(E->GetDistance())) * this->GetCastlePower() * (1);
		double EnemyHealthO = E->gethealth();
		E->sethealth(EnemyHealthO - Dce);
		if (E->gethealth() <= 0)// enqueue in the killed list
		{
			E->SetStatus(KILD);
			E->set_killtime(b->getcurrentstep());
			if (dynamic_cast<Healer*>(E) && E->GetDistance() <= 5)
			{
				this->SetHealth(this->GetHealth() * 1.03);
			}
		}
	}
	else //if the castle attacked fighters using ice
	{
		int F;
		if (E->gettype() == 1)
			F = (int)(((1 / E->GetDistance()) * this->GetCastlePower() * E->gethealth()) / 3) + (2);
		else
			F = (int)(((1 / E->GetDistance()) * this->GetCastlePower() * E->gethealth()) / 3) + (1);
		E->SetStatus(FRST);
		E->set_frost(F);
	}
}

int Castle::getfreezevalue()
{
	return freeze_max;
}
bool Castle::CastleWin()
{
	//Check if fighter, healers, freezers head ==null return true else return false;
	return true;
}
Castle::~Castle()
{

}

void Castle::setattacktype(int type)
{
	attack_type = type;
}
int Castle::getattacktype()
{
	return attack_type;
}

