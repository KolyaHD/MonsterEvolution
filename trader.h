#ifndef TRADER_H
#define TRADER_H

#include "monster.h"
#include <vector>
using namespace std;

class Trader : public Monster {
public:
	Trader(vector<int> inpLocation);
	void setActive();
	bool getActive();
private:
	bool m_active;
};



#endif TRADER_H