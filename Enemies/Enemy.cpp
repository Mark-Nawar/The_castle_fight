#include "Enemy.h"


Enemy::Enemy(int id, int arrTime, int d) :ID(id), ArrvTime(arrTime)
{
	SetDistance(d);
}
Enemy::Enemy(int id, int typ, int arr, int h, int pow, int rld, int spd):ID(id),ArrvTime(arr)
{
	type = typ;
	Health = h;
	power = pow;
	reload_time = rld;
	speed = spd;
	Distance = MaxDistance;
	IsShoot = false;
	isdead = false;
	status = INAC;
	reload_counter = 0;
	original_health = h;
}
Enemy::~Enemy()
{
}

bool Enemy::getisshoot()
{
	return IsShoot;
}
void Enemy::setisshoot(int time)
{
	first_shot = time;
}
void Enemy::setisdead(int time)
{
	 killedTime = time;
}
bool Enemy::getisdead()
{
	return isdead;
}
int Enemy::GetID() const
{
	return ID;
}
int Enemy::gettype() const
{
	return type;
}

void Enemy::SetStatus(ENMY_STATUS s)
{
	status = s;
}
ENMY_STATUS Enemy::GetStatus() const
{
	return status;
}
void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}
void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else if (d <= MinDistance)
		Distance = MinDistance;
	else
		Distance = MaxDistance;
}
int Enemy::GetDistance() const
{
	return Distance;
}
int Enemy::GetArrvTime() const
{
	return ArrvTime;
}
void Enemy::set_firstshoot(int first)
{
	first_shot = first;
	IsShoot = true;
}
int Enemy::get_firstshoot() const
{
	return first_shot;
}
void Enemy::set_killtime(int killtime)
{
	killedTime = killtime;
	isdead = true;
}
int Enemy::get_killtime()const
{
	return killedTime;
}
int Enemy::calculateFD(int arrive, int first)
{
	return first_shot - arrive;
}
int Enemy::calculateKD(int kill, int first)
{
	return killedTime - first_shot;
}
double Enemy::gethealth()const
{
	return Health;
}
void Enemy::sethealth(double health)
{
	Health = health;
}
int Enemy::getpower()const
{
	return power;
}
void Enemy::setpower(int p)
{
	power = p;
}
void Enemy::setspeed(int s)
{
	speed = s;
}
int Enemy::getspeed()const
{
	return speed;
}
void Enemy::set_reloadtime(int r)
{
	reload_time = r;
}
int Enemy::get_reload()
{
	return reload_time;
}
int Enemy::get_frost()
{
	return frost_time_steps;
}
void Enemy::set_frost(int f)
{
	frost_time_steps = f;
}
int Enemy::get_frost_counter()
{
	return frost_counter;
}
void Enemy::setfrostcounter(int FC)
{
	frost_counter = FC;
}
int Enemy::get_reloadcounter()const
{
	return reload_counter;
}
void Enemy::decreloadcounter()
{
	reload_counter--;
	if (reload_counter < 0)
		reload_counter = 0;
}

double Enemy::getOriginalHealth() const
{
	return original_health;
}