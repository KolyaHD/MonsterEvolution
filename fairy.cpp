#include "fairy.h"
#include "monster.h"
#include <vector>
#include <string>
#include "player.h"

using namespace std;

Fairy::Fairy(vector<int> inpLocation) : Monster("Fairy", inpLocation)
{
	m_active = false;
}

Fairy::~Fairy()
{

}

//return whether or not the fairy has been activated
bool Fairy::getActive()
{
	return m_active;
}

//set whether it is active
void Fairy::setActive(bool inpBool)
{
	m_active = inpBool;
}

//return which player the fairy is imprinted on
Player * Fairy::belongsToPlayer()
{
	return m_ownedPlayer;
}

//imprint the fairy to a player
void Fairy::setToPlayer(Player * inpPlayer)
{
	m_ownedPlayer = inpPlayer;
}