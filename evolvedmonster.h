#ifndef EVOLVEDMONSTER_H
#define EVOLVEDMONSTER_H

#include "monster.h"
#include <string>
#include <vector>
using namespace std;

class Evolvedmonster : public Monster {
private:
	int m_modifier;
public:
	Evolvedmonster(vector<Monster*> inpMonsters);
	int getModifier();
	int skillLevel();
};


#endif