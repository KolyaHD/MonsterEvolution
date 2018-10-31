#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "monster.h"
#include "evolvedmonster.h"


using namespace std;

class Player : public Monster{
private:
	vector<Monster*> m_monsterList;
	bool m_hasEvolvedMon;
	string m_name;
	bool m_hasLamp;

public:
	Player(vector<int> location);
	bool m_moveUp();
	bool m_moveRight();
	bool m_moveLeft();
	bool m_moveDown();
	void addMonster(Monster * inpMonster);
	void displayInventory();
	Evolvedmonster * m_evMon;
	bool hasEvolvedMonster();
	void setName(string inpName);
	string getName();
	int hasMostOfMonster();
	Monster * getMonster(int inpIndex);
	void setHasLamp(bool inpBool);
	bool getHasLamp();
	int getMonsterNumber();
	void displayStats();
};



#endif