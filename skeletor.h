#ifndef SKELETOR_H
#define SKELETOR_H

#include "monster.h"
#include <string>
#include <vector>
using namespace std;

class Skeletor : public Monster {
private:
	int m_modifier;
public:
	Skeletor(vector<int> location);
	int getModifier();
	int skillLevel();
};



#endif