#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "monster.h"
#include "evolvedmonster.h"
#include "skeletor.h"
#include <string>
#include <vector>
#include "fairy.h"
#include "trader.h"

using namespace std;


class Game {
private:
	vector<Monster*> m_monsters;
	int m_playerNumber;
	bool m_hiddenBoard;
	vector<string> m_board;
public:
	Player* m_player1;
	Player* m_player2;
	Game(int playerNum);
	void displayBoard();
	int monsterAtPosition(vector<int> inpPosition);
	void setHiddenBoard(bool hidden);
	Monster * getMonster(int index);
	void randomiseLocation(Monster* inpMonster);
	void addMonster(Monster* inpMonster);
	bool getHiddenBoard();
};


#endif