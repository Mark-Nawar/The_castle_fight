#include "Healer.h"

// to avoid any ambuguity in the equations of the healers it is assumed that healers cannot heal one another
// other wise the game will be biased towards the enemies
Healer::Healer(int id, int arrtime, int d) :Enemy(id, arrtime, d)
{
	// possible to add a K memeber function in the future not sure
	dir = 1;
}
Healer::Healer(int id, int type, int arr, int health, int power, int rld, int spd) : Enemy(id, type, arr, health, power, rld, spd)
{
	// possible to add a K memeber function in the future not sure
	dir = 1;
}
void Healer::Move(Battle* hot_battle)// the move function is diffenet when it comes to the healers they can go backwards aswell
{
	int s = speed;
	if (Health < (original_health / 2))
		s = s / 2;
	if (dir)
	{
		int currDistance = Distance - s;
		if (currDistance < 2)
		{
			SetDistance(s - Distance + 4); // current +4 same 
			dir = 0; // change direction when a U turn happens
		}
		else
			SetDistance(currDistance);
		if (currDistance == 2)
			dir = 0;
	}
	else
	{
		int currDistance = Distance + s;
		if (currDistance > 60)
		{
			SetDistance(120 - s - Distance); //120 - current same
			dir = 1;// change the diretion when a U turn happens
		}
		else
			SetDistance(currDistance);
		if (currDistance == 60)
			dir = 1;
	}
}
void Healer::Act(Battle* hot_battle)
{
	int reload_current = this->get_reloadcounter();// get the reload time counter of the fihter

	if (reload_current > 0 && status == ACTV) // Decrement reload counter only
	{
		reload_counter--;
		return;
	}
	else if (reload_current == 0 && status == ACTV)
	{
		Enemy* temp;
		temp = hot_battle->GetCurrentEnemy();

		int diffDistance = temp->GetDistance() - Distance;
		double ratio = 1;
		if (Health < (original_health / 2))
			ratio = 0.5;
		// Increase Enemy's health by function

		if (dir)
		{
			if (diffDistance == -2) // If Enemy is far then healing will be less effective
			{
				double healedHealth = temp->gethealth() + (power / (temp->gethealth() * 2)) * ratio;
				if (healedHealth >= temp->getOriginalHealth())
					temp->sethealth(temp->getOriginalHealth());
				else
					temp->sethealth(healedHealth);

			}
			else if (diffDistance == -1 || diffDistance == 0)
			{
				double healedHealth = temp->gethealth() + (power / (temp->gethealth())) * ratio;
				if (healedHealth >= temp->getOriginalHealth())
					temp->sethealth(temp->getOriginalHealth());
				else
					temp->sethealth(healedHealth);
			}
		}
		else
		{
			if (diffDistance == 2) // If Enemy is far then healing will be less effective
			{
				double healedHealth = temp->gethealth() + (power / (temp->gethealth() * 2)) * ratio;
				if (healedHealth >= temp->getOriginalHealth())
					temp->sethealth(temp->getOriginalHealth());
				else
					temp->sethealth(healedHealth);

			}
			else if (diffDistance == 1 || diffDistance == 0)
			{
				double healedHealth = temp->gethealth() + (power / (temp->gethealth())) * ratio;
				if (healedHealth >= temp->getOriginalHealth())
					temp->sethealth(temp->getOriginalHealth());
				else
					temp->sethealth(healedHealth);
			}
		}
		reload_counter = reload_time; // Reset reload counter
	}
}

int Healer::GETPERIORITY()
{
	return 0;
}