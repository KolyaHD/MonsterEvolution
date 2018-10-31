#include "minotaur.h"

Minotaur::Minotaur(vector<int> inpLocation) : Monster("Minotaur", inpLocation)
{
	//set stats
	m_skillLevel = 9;
	m_health = 1;
}