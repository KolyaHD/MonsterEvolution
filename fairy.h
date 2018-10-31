#ifndef FAIRY_H
#define FAIRY_H

#include "monster.h"
#include "player.h"
#include <vector>
using namespace std;

class Fairy : public Monster{
private:
	bool m_active;
	Player * m_ownedPlayer;
public:
	Fairy(vector<int> inpLocation);
	bool getActive();
	void setActive(bool inpBool);
	Player * belongsToPlayer();
	void setToPlayer(Player * inpPlayer);
	~Fairy();
};


#endif