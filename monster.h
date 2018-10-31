#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <vector>

using namespace std;

class Monster {
protected:
	string m_type;
	int m_skillLevel;
	int m_health;
	vector<int> m_location;
	bool inInventory;
	bool m_isAlive;
public:
	string getType();
	char getInitial();
	virtual int skillLevel();
	int getHealth();
	void takeDamage(int inpDamage);
	vector<int> getLocation();
	virtual void displayStats();
	void setAlive(bool inpAlive);
	bool getAlive();
	void setLocation(vector<int> inpLocation);
	void incrementSkill();

	Monster(string type, vector<int> location);
	virtual ~Monster();
};


#endif