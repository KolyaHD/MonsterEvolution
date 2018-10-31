#include "monster.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

Monster::Monster(string type, vector<int> location) : m_type(type), m_location(location)
{
	//generate stats
	m_skillLevel = rand() % 3 + 1;
	m_health = rand() % 4 + 3;
	inInventory = false;
	m_isAlive = true;
}

Monster::~Monster()
{
	
}

//get skill level
int Monster::skillLevel()
{
	return m_skillLevel;
}

//get the health
int Monster::getHealth()
{
	return m_health;
}

//cause damage to the monster
void Monster::takeDamage(int inpDamage)
{
	m_health -= inpDamage;
}

//get monster type
string Monster::getType()
{
	return m_type;
}

//get monster location
vector<int> Monster::getLocation()
{
	return m_location;
}

//get first character of type string
char Monster::getInitial()
{
	return m_type[0];
}

//display the monster stats
void Monster::displayStats()
{
	cout << m_type << ": <Skill: " << m_skillLevel << "> <Health: " << m_health << ">\n";
}

//set whether the monster is alive
void Monster::setAlive(bool inpAlive)
{
	m_isAlive = inpAlive;
}

//return whether monster is alive
bool Monster::getAlive()
{
	return m_isAlive;
}

//set monster location
void Monster::setLocation(vector<int> inpLocation)
{
	m_location = inpLocation;
}

//increment the skill level
void Monster::incrementSkill()
{
	m_skillLevel++;
}