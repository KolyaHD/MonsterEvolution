#include "skeletor.h"
#include <vector>
using namespace std;

Skeletor::Skeletor(vector<int> location) : Monster("Skeletor", location)
{
	//generate stats
	m_skillLevel = 10;
	m_health = 20;
	m_modifier = 2;
}

//return modifier
int Skeletor::getModifier()
{
	return m_modifier;
}

//return skill level plus modifier
int Skeletor::skillLevel()
{
	return (m_skillLevel + m_modifier);
}