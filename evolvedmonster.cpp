#include "evolvedmonster.h"
#include "monster.h"
#include <string>
#include <vector>

using namespace std;


Evolvedmonster::Evolvedmonster(vector<Monster*> inpMonsters) : Monster((*inpMonsters[0]).getType(), { 0,0 })
{
	m_skillLevel = 0;
	//addd up all skill levels
	for (int i = 0; i < inpMonsters.size(); i++)
	{
		m_skillLevel += (*inpMonsters[i]).skillLevel();
	}

	m_health = 0;
	//add up all health
	for (int i = 0; i < inpMonsters.size(); i++)
	{
		m_health += (*inpMonsters[i]).getHealth();
	}

	//generate modifier and add to skill level
	if ((*inpMonsters[0]).getType() == "Bugbear")
	{
		m_modifier = 1;
	}
	else if ((*inpMonsters[0]).getType() == "Platypie")
	{
		m_modifier = 2;
	}
	else if ((*inpMonsters[0]).getType() == "Emoo")
	{
		m_modifier = 3;
	}

	//clean up all input monsters
	for (int i = 0; i < inpMonsters.size(); i++)
	{
		delete inpMonsters[i];
	}


}

//return modifier
int Evolvedmonster::getModifier()
{
	return m_modifier;
}

//return skill level plus modifier
int Evolvedmonster::skillLevel()
{
	return (m_skillLevel + m_modifier);
}