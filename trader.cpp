#include "trader.h"

Trader::Trader(vector<int> inpLocation) : Monster("Trader", inpLocation), m_active(false)
{
	//generate stats
	m_skillLevel = 7;
	m_health = 3;
	
}

//set whether the trader has been found
void Trader::setActive()
{
	m_active = true;
}

//get whether the trader has been found
bool Trader::getActive()
{
	return m_active;
}