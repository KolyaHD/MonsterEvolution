#include "game.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


Game::Game(int playerNum)
{
	//create a vector of position vectors
	vector<vector<int>> positions;

	//create skeletor and push it into the vector of monsters and make sure the position is maked for setup
	int skeletorPositionx = 20;
	int skeletorPositiony = rand() % 8 + 2;
	m_monsters.push_back(new Skeletor({ skeletorPositionx, skeletorPositiony }));
	positions.push_back({ skeletorPositionx, skeletorPositiony });

	//create 3 monsters one the three sides of skeletor and add to monster array
	m_monsters.push_back(new Monster("Minion", { skeletorPositionx - 1, skeletorPositiony }));
	m_monsters.push_back(new Monster("Minion", { skeletorPositionx, skeletorPositiony + 1 }));
	m_monsters.push_back(new Monster("Minion", { skeletorPositionx, skeletorPositiony - 1 }));
	positions.push_back({ skeletorPositionx - 1, skeletorPositiony });
	positions.push_back({ skeletorPositionx, skeletorPositiony + 1 });
	positions.push_back({ skeletorPositionx, skeletorPositiony - 1 });
	
	
	//create player 1 postion
	m_playerNumber = playerNum;
	vector<int> player1Position = { 1, rand() % 10 + 1 };
	positions.push_back(player1Position);
	m_player1 = new Player(player1Position);
	
	if (playerNum == 2)
	{
		//create player 2 postion
		vector<int> player2Position;
		//make sure its not the same spot as player 1
		do
		{
			player2Position = { 1, rand() % 10 + 1 };
		} while (player1Position == player2Position);
		positions.push_back(player2Position);
		m_player2 = new Player(player2Position);
	}

	for (int i = 0; i < 42; i++)
	{
		bool valid = true;
		do
		{
			//generate random spot
			valid = true;
			vector<int> v1 = { rand() % 20 + 1, rand() % 10 + 1 };

			//make sure no other monster is there
			for (int j = 0; j < positions.size(); j++)
			{
				if (v1 == positions[j])
				{
					valid = false;
					break;
				}
			}
			
			//create new appropriate monster
			if (valid)
			{
				if (i < 10)
				{
					m_monsters.push_back(new Monster("Bugbear", v1));
				}
				else if (i < 20)
				{
					m_monsters.push_back(new Monster("Platypie", v1));
				}
				else if (i < 30)
				{
					m_monsters.push_back(new Monster("Emoo", v1));
				}
				else if (i < 40)
				{
					m_monsters.push_back(new Monster("Octopod", v1));
				}
				else if (i < 41)
				{
				m_monsters.push_back(new Fairy(v1));
				}
				else if (i < 42)
				{
					m_monsters.push_back(new Trader(v1));
				}
				//make sure the monster is maked in position
				positions.push_back(v1);

			}
			//clear postion vector
			v1.clear();
		} while (!valid);
	}

	//hide or show board


	//intake board
	ifstream input;
	input.open("Board.txt");

	string temp;

	//make and array of board lines
	for (int i = 0; i < 10; i++)
	{
		getline(input, temp);
		m_board.push_back(temp);

	}
	input.close();
}

int Game::monsterAtPosition(vector<int> inpPosition)
{
	//check if there is a monster at location
	for (int i = 0; i < m_monsters.size(); i++)
	{
		if (inpPosition == (*m_monsters[i]).getLocation())
		{
			//return index
			return i;
		}
	}
	if (m_playerNumber == 2 && (*m_player1).getLocation() == (*m_player2).getLocation() && (*m_player1).getLocation() == inpPosition)
	{
		//if both players are at same location
		return -1;
	}

	//if no monster or player
	return -2;
}

void Game::displayBoard()
{


	vector<string> tempBoard = m_board;

	if (!m_hiddenBoard)
	{
		//for very monster, get location and print initial at approriate char in board
		for (int i = 0; i < m_monsters.size(); i++)
		{
			vector<int> monsterloc = (*m_monsters[i]).getLocation();
			tempBoard[monsterloc[1] - 1][2 * monsterloc[0] - 2] = (*m_monsters[i]).getInitial();
		}
	}
	else
	{
		for (int i = 0; i < m_monsters.size(); i++)
		{
			//for the trader...
			if ((*m_monsters[i]).getType() == "Trader")
			{
				//create trader pointer
				Trader * tempTrader = static_cast<Trader*>(m_monsters[i]);
				if ((*tempTrader).getActive())
				{
					//if it has been found, always display the initial
					vector<int> monsterloc = (*tempTrader).getLocation();
					tempBoard[monsterloc[1] - 1][2 * monsterloc[0] - 2] = (*m_monsters[i]).getInitial();
				}
			}
			//for the fairy...
			else if ((*m_monsters[i]).getType() == "Fairy")
			{
				//create fairy pointer
				Fairy * tempFairy = static_cast<Fairy*>(m_monsters[i]);
				if ((*tempFairy).getActive())
				{
					//if it is active, always display it
					vector<int> monsterloc = (*tempFairy).getLocation();
					tempBoard[monsterloc[1] - 1][2 * monsterloc[0] - 2] = (*m_monsters[i]).getInitial();
				}
			}
		}


		Player * tempPlayer;
		//for each player...
		for (int count = 1; count <= m_playerNumber; count++)
		{
			if (count == 1)
			{
				tempPlayer = m_player1;
			}
			else
			{
				tempPlayer = m_player2;
			}

			if ((*tempPlayer).getHasLamp())
			{
				//print the initial of any monster in a 5x5 area around the player, if he has a lamp
				vector<int> tempLocation = (*tempPlayer).getLocation();
				for (int i = -2; i < 3; i++)
				{
					for (int j = -2; j < 3; j++)
					{
						int isMonsterTemp = monsterAtPosition({ tempLocation[0] + i, tempLocation[1] + j });
						if (isMonsterTemp >= 0 && !(j == 0 && i == 0))
						{
							tempBoard[tempLocation[1] + j - 1][2 * (tempLocation[0] + i) - 2] = (*m_monsters[isMonsterTemp]).getInitial();
						}
					}
				} 
			}
			

		}
	}

	//get player 1 location and add "1" to correct char in board
	vector<int> player1loc = (*m_player1).getLocation();
	tempBoard[player1loc[1] - 1][2 * player1loc[0] - 2] = '1';

	if (m_playerNumber == 2)
	{
		//get player 2 location and add "2" to correct char in board
		vector<int> player2loc = (*m_player2).getLocation();
		tempBoard[player2loc[1] - 1][2 * player2loc[0] - 2] = '2';
	}

	//print out the entire board with its alterations from above
	for (int i = 0; i < tempBoard.size(); i++)
	{
		cout << tempBoard[i] << endl;
	}

}

//set whether board is hidden
void Game::setHiddenBoard(bool hidden)
{
	m_hiddenBoard = hidden;
}

//get monster out of vector
Monster * Game::getMonster(int index)
{
	Monster * outMonster = m_monsters[index];
	//clean up
	m_monsters.erase(m_monsters.begin() + index);
	return outMonster;
}

//randomise monster location
void Game::randomiseLocation(Monster* inpMonster)
{
	int locationStat = 0;
	vector<int> locationTest;
	//generate random location and make sure its empty
	while (locationStat != -2)
	{
		locationTest.clear();
		locationTest.push_back(rand() % 20 + 1);
		locationTest.push_back(rand() % 10 + 1);
		locationStat = monsterAtPosition(locationTest);
	}
	(*inpMonster).setLocation(locationTest);
}

//add monster to vector
void Game::addMonster(Monster* inpMonster)
{
	m_monsters.push_back(inpMonster);
}

//get whether the board is hidden or not
bool Game::getHiddenBoard()
{
	return m_hiddenBoard;
}