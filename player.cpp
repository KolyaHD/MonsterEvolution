#include "player.h"
#include <vector>
#include <iostream>
using namespace std;

Player::Player(vector<int> location) : Monster("Player",{location}), m_hasEvolvedMon(false), m_hasLamp(false)
{
	//generate stats
	m_skillLevel = 6;
	m_health = 10;
}

bool Player::m_moveUp()
{
	vector<int> temp = m_location;
	//make sure move is valid and then change location
	if (temp[1] > 1)
	{
		m_location = { temp[0], temp[1]-1 };
		return true;
	}
	return false;
}

bool Player::m_moveLeft()
{
	vector<int> temp = m_location;
	//make sure move is valid and then change location
	if (temp[0] > 1)
	{
		m_location = { temp[0]-1, temp[1] };
		return true;
	}
	return false;
}

bool Player::m_moveRight()
{
	vector<int> temp = m_location;
	//make sure move is valid and then change location
	if (temp[0] < 20)
	{
		m_location = { temp[0]+1, temp[1] };
		return true;
	}
	return false;
}

bool Player::m_moveDown()
{
	vector<int> temp = m_location;
	//make sure move is valid and then change location
	if (temp[1] < 10)
	{
		m_location = { temp[0], temp[1]+1 };
		return true;
	}
	return false;
}

//add monster to player inventory
void Player::addMonster(Monster * inpMonster)
{
	m_monsterList.push_back(inpMonster);

	if (!m_hasEvolvedMon)
	{
		//if the player doesnt already have an evolved moster, check if the player has 5 of kind
		vector<int> monsterCount;
		vector<Monster*> monsterVector;
		for (int i = 0; i < m_monsterList.size(); i++)
		{
			//count monsters
			if ((*m_monsterList[i]).getType() == (*inpMonster).getType())
			{
				monsterCount.push_back(i);
				monsterVector.push_back(m_monsterList[i]);
				
			}
		}

		if (monsterCount.size() >= 5)
		{
			//if it has 5 of a kind, make an evolved monster and clean up vector
			m_hasEvolvedMon = true;
			for (int count = (monsterCount.size()-1); count >= 0; count--)
			{
				m_monsterList.erase(m_monsterList.begin() + monsterCount[count]);
			}
			m_evMon = new Evolvedmonster(monsterVector);
			cout << "Your Monsters evolved into an Evolved " << (*m_evMon).getType() << "!" << endl;
			
		}

	}

}

void Player::displayInventory()
{
	//make vecotor of vectors of monsters
	vector<vector<Monster *>> counterVec;
	for (int i = 0; i < m_monsterList.size(); i++)
	{
		bool foundType = false;
		for (int j = 0; j < counterVec.size(); j++)
		{
			//if the type already has its own vector, add monster to said vecotr. if not, create new vector
			if ((*m_monsterList[i]).getType() == (*counterVec[j][0]).getType())
			{
				counterVec[j].push_back(m_monsterList[i]);
				foundType = true;
				break;
			}

		}
		if (!foundType)
		{
			vector<Monster*> tempVec;
			tempVec.push_back(m_monsterList[i]);
			counterVec.push_back(tempVec);
		}
	}

	cout << "Inventory:\n";

	cout << "Player Stats:\n";
	displayStats();

	cout << "Monsters: (" << m_monsterList.size() + m_hasEvolvedMon << ")\n";
	
	if (m_hasEvolvedMon)
	{
		cout << "Evolved Monster:\n";
		(*m_evMon).displayStats();
	}

	//for every monster type, print out all monsters
	for (int i = 0; i < counterVec.size(); i++)
	{
		cout << (*counterVec[i][0]).getType() << ": (" << counterVec[i].size() << ")" << endl;
		for (int j = 0; j < counterVec[i].size(); j++)
		{
			(*counterVec[i][j]).displayStats();
		}
	}
}

//check whther player has evolved monster
bool Player::hasEvolvedMonster()
{
	return m_hasEvolvedMon;
}

//set player name
void Player::setName(string inpName)
{
	m_name = inpName;
}

//get player name
string Player::getName()
{
	return m_name;
}

//check what monster the player has most of
int Player::hasMostOfMonster()
{
	//create a vector of vecotrs of monsters
	vector<vector<Monster *>> counterVec;
	//for every monster...
	for (int i = 0; i < m_monsterList.size(); i++)
	{
		bool foundType = false;
		for (int j = 0; j < counterVec.size(); j++)
		{
			//if the monster type already has a vector, add to vector. if not, make new vector 
			if ((*m_monsterList[i]).getType() == (*counterVec[j][0]).getType())
			{
				counterVec[j].push_back(m_monsterList[i]);
				foundType = true;
				break;
			}

		}
		if (!foundType)
		{
			vector<Monster*> tempVec;
			tempVec.push_back(m_monsterList[i]);
			counterVec.push_back(tempVec);
		}
	}

	//for the type with the most monsters, return the first one
	int biggestNumber = 0;
	string biggestType = "";
	for (int i = 0; i < counterVec.size(); i++)
	{
		if (counterVec[i].size() > biggestNumber)
		{
			biggestNumber = counterVec[i].size();
			biggestType = (*counterVec[i][0]).getType();
		}

	}

	//return that there is not monster
	if (biggestNumber == 0)
	{
		return -1;
	}
	else
	{
		//return index of first monster of most common type
		int i = -1;
		string tempType = "";
		do
		{
			i++;
			tempType = (*m_monsterList[i]).getType();
		} while (tempType != biggestType);
		return i;
	}



}

//get monster from vector
Monster * Player::getMonster(int inpIndex)
{
	Monster * tempReturn = m_monsterList[inpIndex];
	m_monsterList.erase(m_monsterList.begin() + inpIndex);
	return tempReturn;

}

//set whether player has lamp
void Player::setHasLamp(bool inpBool)
{
	m_hasLamp = inpBool;
}

//check whether player has lamp
bool Player::getHasLamp()
{
	return m_hasLamp;
}

//get the amount of monsters the player has
int Player::getMonsterNumber()
{
	return m_monsterList.size();
}

//display player stats
void Player::displayStats()
{
	cout << m_name << ": <Skill: " << m_skillLevel << "> <Health: " << m_health << ">\n";
}