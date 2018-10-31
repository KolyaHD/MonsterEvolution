#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include "evolvedmonster.h"
#include "game.h"
#include "monster.h"
#include "player.h"
#include "skeletor.h"
#include "fairy.h"
#include "minotaur.h"
#include "trader.h"



int main()
{
	//seed random numbers
	srand(time(NULL));

	//initiate game
	cout << "Welcome to this Dungeon Crawler!\n\n";
	string returnStr;
	int playeNum;

	//get number of players
	do
	{
		cout << "How many players are playing?(1/2) ";
		cin >> returnStr;
		if (returnStr == "1")
		{
			playeNum = 1;
		}
		else if (returnStr == "2")
		{
			playeNum = 2;
		}

		if (returnStr != "1" && returnStr != "2")
		{
			cout << "Invalid Input, please reenter!\n";
		}
	} while (returnStr != "1" && returnStr != "2");
	
	//set up game
	Game game1(playeNum);
	game1.setHiddenBoard(true);

	//get names of players
	{
		cout << "Player 1, what is your name? ";
		string tempName;
		cin >> tempName;
		(*game1.m_player1).setName(tempName);

		if (playeNum == 2)
		{
			cout << "Player 2, what is your name? ";
			cin >> tempName;
			(*game1.m_player2).setName(tempName);
		}

	}

	//display board
	cout << "This is your board:\n";
	game1.displayBoard();

	//vairables for game loop

	//set current player
	Player * currentPlayer;
	currentPlayer = game1.m_player1;
	
	//start game
	cout << (*currentPlayer).getName() << ", make your move!\n";

	//gameloop
	while (true)
	{
		//set loop
		bool success;
		do
		{
			//get direction of motion
			string choiceStr;
			do
			{
				cout << "In which direction would you like to move?(w/a/s/d) ";
				cin >> choiceStr;
				if (choiceStr == "inventory")
				{
					(*currentPlayer).displayInventory();
				}
				else if (choiceStr == "lamp")
				{
					(*currentPlayer).setHasLamp(!(*currentPlayer).getHasLamp());
					system("CLS");
					game1.displayBoard();
				}
				else if (choiceStr == "visible")
				{
					game1.setHiddenBoard(!game1.getHiddenBoard());
					system("CLS");
					game1.displayBoard();
				}
				else if (choiceStr != "w" && choiceStr != "s" && choiceStr != "a" && choiceStr != "d")
				{
					cout << "Invalid Entry: Please reenter!\n";
				}
				
			} while (choiceStr != "w" && choiceStr != "s" && choiceStr != "a" && choiceStr != "d");

			//move in required direction
			if (choiceStr == "w")
			{
				success = (*currentPlayer).m_moveUp();
			}
			else if (choiceStr == "a")
			{
				success = (*currentPlayer).m_moveLeft();
			}
			else if (choiceStr == "s")
			{
				success = (*currentPlayer).m_moveDown();
			}
			else
			{
				success = (*currentPlayer).m_moveRight();
			}
			if (!success)
			{
				cout << "Invalid Move: Please Reselect!\n";
			}
		} while (!success);

		//display board for next move
		system("CLS");
		game1.displayBoard();

		//set up the hostile and friendly monster
		Monster * currentHostileMonster;
		Monster * currentFriendlyMonster;

		//get monster at position
		// monsterIndex: -2=no monster, -1=other player, >-1=index of monster at postition
		int monsterIndex = game1.monsterAtPosition((*currentPlayer).getLocation());
		if (monsterIndex == -1)
		{
			//randomise location for both
			game1.randomiseLocation(game1.m_player1);
			game1.randomiseLocation(game1.m_player2);

			system("CLS");
			game1.displayBoard();

			//encountered the other player
			cout << "You have encountered another player!\nYour locations have been randomised!\n";
		}
		else if (monsterIndex > -1)
		{
			//set up hostile monster for correct monster
			currentHostileMonster = game1.getMonster(monsterIndex);
			cout << "A wild " << (*currentHostileMonster).getType() << " appears!\n";
			//display monster stats
			(*currentHostileMonster).displayStats();
			
			//set up friendly monster from player
			currentFriendlyMonster = currentPlayer;

			//if monster is not sceletor, display the player stats
			if ((*currentHostileMonster).getType() != "Skeletor")
			{
				(*currentFriendlyMonster).displayStats();
			}
			
			//for all 3 basic friendly monsters
			if ((*currentHostileMonster).getType() == "Bugbear" || (*currentHostileMonster).getType() == "Platypie" || (*currentHostileMonster).getType() == "Emoo")
			{
				//roll dice and catch monster
				if ((rand() % 6 + 1) >= (*currentHostileMonster).skillLevel())
				{
					//catch monster
					cout << "You caught the Monster!\n";
					(*currentPlayer).addMonster(currentHostileMonster);
				}
				else
				{
					//dont catch monster
					cout << "You dont have enough skill to control the Monster,\n it escapes!\n";
					delete currentHostileMonster;
				}
			}
			//for monster octopod and minion
			else if ((*currentHostileMonster).getType() == "Octopod" || (*currentHostileMonster).getType() == "Minion")
			{
				cout << "You Fight the Monster!\n";
				//battle monster until one is dead
				while ((*currentFriendlyMonster).getHealth() > 0 && (*currentHostileMonster).getHealth() > 0)
				{
					//roll dice for both monsters
					int friendlyRandNumber = (rand() % 6 + 1 + (*currentFriendlyMonster).skillLevel());
					int hostileRandNumber = (rand() % 6 + 1 + (*currentHostileMonster).skillLevel());
					//decide who takes damage
					if (friendlyRandNumber > hostileRandNumber)
					{
						//hostile monster takes damage
						(*currentHostileMonster).takeDamage(1);
					}
					else if (friendlyRandNumber < hostileRandNumber)
					{
						//friendly monster takes damage
						(*currentFriendlyMonster).takeDamage(1);
					}
					else
					{
						//nothing happens
					}
				}
				if ((*currentPlayer).getHealth() > 0)
				{
					//if player wins, display end stats
					delete currentHostileMonster;
					cout << "You win the fight with the following stats!\n";
					(*currentFriendlyMonster).displayStats();
				}
				else
				{
					//set player to dead
					(*currentPlayer).setAlive(false);
				}
			}
			else if ((*currentHostileMonster).getType() == "Fairy")
			{
				//make a fairy pointer for monster pointer
				Fairy * tempFairy = static_cast<Fairy*>(currentHostileMonster);
				
				//if the fairy is has not yet been activated by any other player
				if (!(*tempFairy).getActive())
				{
					//set fairy to active
					(*tempFairy).setActive(true);
					//bind fairy to one player
					(*tempFairy).setToPlayer(currentPlayer);
					//display dialogue
					cout << "Fairy: " << (*currentPlayer).getName() << ", I am the Great Fountain Fairy!\n";
					cout << "Fairy: " << "Please help me defeat the evil Minotaur that plagues the land!\n";
					cout << "Fairy: " << "I have marked the location on the map!\n";
					//send the fairy to some other square
					game1.randomiseLocation(currentHostileMonster);
					game1.addMonster(currentHostileMonster);
				}
				//if the fairy has been activated, but is not bound to the particualr player that finds it
				else if ((*tempFairy).getActive() && (*tempFairy).belongsToPlayer() != currentPlayer)
				{
					//tell the player
					cout << "Fairy: You are not the hero I am waiting for!\n";
				}
				//if the fairy is active and the correct player arrives
				else
				{
					//dispaly dialogue
					cout << "You are just in time!\n";
					cout << "The Minotaur is even more dangerous that ever!\n";

					//make a minotaur
					Minotaur minotaur({ 0, 0 });
					minotaur.displayStats();

					//get whether player want to fight minotaur
					string minotaurChoice;
					do
					{
						cout << "Are you brave enough to fight this minotaur?(y/n)\n";
						cin >> minotaurChoice;
						if (minotaurChoice != "y" && minotaurChoice != "n")
						{
							cout << "Invalid Entry, Please Reenter!\n";
						}

					} while (minotaurChoice != "y" && minotaurChoice != "n");

					//decide whether player fight or not
					if (minotaurChoice == "y")
					{
						//fight the minotaur until one is dead
						while ((*currentFriendlyMonster).getHealth() > 0 && minotaur.getHealth() > 0)
						{
							int friendlyRandNumber = (rand() % 6 + 1 + (*currentFriendlyMonster).skillLevel());
							int hostileRandNumber = (rand() % 6 + 1 + minotaur.skillLevel());
							if (friendlyRandNumber > hostileRandNumber)
							{
								minotaur.takeDamage(1);
							}
							else if (friendlyRandNumber < hostileRandNumber)
							{
								(*currentFriendlyMonster).takeDamage(1);
							}
							else
							{

							}
						}
						//if player survives
						if ((*currentPlayer).getHealth() > 0)
						{
							//clean up
							delete currentHostileMonster;
							
							if ((*currentPlayer).hasEvolvedMonster())
							{
								//up the skill points of the evolved monster
								(*(*currentPlayer).m_evMon).incrementSkill();
								cout << "The skill level of your Evolved " << (*(*currentPlayer).m_evMon).getType() << " was increased by 1!\n";
							}
							else
							{
								//up the player level skill
								(*currentPlayer).incrementSkill();
								cout << "Your skill level was increased by 1!\n";
							}
							
							//display winning stats
							cout << "You win the fight with the following stats!\n";
							(*currentPlayer).displayStats();
							if ((*currentPlayer).hasEvolvedMonster())
							{
								(*(*currentPlayer).m_evMon).displayStats();
							}
						}
						else
						{
							//set player to dead
							(*currentPlayer).setAlive(false);
						}
					}
					else
					{
						//if doesnt want to fight minotaur, display passive aggressive message
						cout << "I agree! Only the strongest and bravest warriers can beat this beast!\n";
					}

					
				}
			}
			//if the monster encountered is a trader
			else if ((*currentHostileMonster).getType() == "Trader")
			{
				//make a trader pointer and set the traider to be active in displaying on the map
				{
					Trader * tempTrader = static_cast<Trader*>(currentHostileMonster);
					(*tempTrader).setActive();
				}

				//display dialogue
				cout << "Trader: Greetings Traveler!\n";

				//if player has evolved monster
				if ((*currentPlayer).hasEvolvedMonster())
				{
					//get choice of trade, not trade or fight
					string choiceTemp;
					do
					{
						cout << "Trader: Would you like to trade 5 heats off your evolved Monster,\nfor a lantern?(yes/no/attack)";
						cin >> choiceTemp;
						if (choiceTemp != "yes" && choiceTemp != "no" && choiceTemp != "attack")
						{
							cout << "Invalid Entry, Please Reenter!";
						}
					} while (choiceTemp != "yes" && choiceTemp != "no" && choiceTemp != "attack");

					if (choiceTemp == "yes")
					{
						//trade
						//damage evolved monster
						(*(*currentPlayer).m_evMon).takeDamage(5);
						//give player a lamp
						(*currentPlayer).setHasLamp(true);
						cout << "Trader: Nice doing business with you!\n";
						cout << "You gained a Lamp!\n";
						//return trader to game
						game1.addMonster(currentHostileMonster);
					}
					else if (choiceTemp == "attack")
					{
						//attack till one is dead
						while ((*currentFriendlyMonster).getHealth() > 0 && (*currentHostileMonster).getHealth() > 0)
						{
							int friendlyRandNumber = (rand() % 6 + 1 + (*currentFriendlyMonster).skillLevel());
							int hostileRandNumber = (rand() % 6 + 1 + (*currentHostileMonster).skillLevel());
							if (friendlyRandNumber > hostileRandNumber)
							{
								(*currentHostileMonster).takeDamage(1);
							}
							else if (friendlyRandNumber < hostileRandNumber)
							{
								(*currentFriendlyMonster).takeDamage(1);
							}
							else
							{

							}
						}
						//if player survives
						if ((*currentFriendlyMonster).getHealth() > 0)
						{
							cout << (*currentPlayer).getName() << ", you win!\n";
							cout << "You take the Lamp from his lifeless body!\n";
							//display stats
							cout << "You survive with the following stats:\n";
							(*currentPlayer).displayStats();
							//give player lamp
							(*currentPlayer).setHasLamp(true);
							//clean up
							delete currentHostileMonster;
						}
						else
						{
							//set the player to dead
							(*currentPlayer).setAlive(false);
						}
					}
					else
					{
						//when no trade is selected, do nothing and add trader back to game
						cout << "Fair enough, that offer still stands though!\n";
						game1.addMonster(currentHostileMonster);
					}
				}
				//if player does not have a evelved mosnter and has some other monsters
				else if ((*currentPlayer).getMonsterNumber() > 0)
				{
					//get the monster of the type hich the player has most of
					int mostMonsterIndex = (*currentPlayer).hasMostOfMonster();
					Monster * selectedMonster = (*currentPlayer).getMonster(mostMonsterIndex);
					//dsiplay dialogue and stats
					cout << "Trader: I admire one of your monsters!\n";
					(*selectedMonster).displayStats();
					
					//get choice
					string choiceTemp;
					do
					{
						cout << "Trader: Would you perhaps like to trade it for a lantern?(yes/no/attack)";
						cin >> choiceTemp;
						if (choiceTemp != "yes" && choiceTemp != "no" && choiceTemp != "attack")
						{
							cout << "Invalid Entry, Please Reenter!";
						}
					} while(choiceTemp != "yes" && choiceTemp != "no" && choiceTemp != "attack");

					if (choiceTemp == "yes")
					{
						//if trade
						//clean up
						delete selectedMonster;
						//give lamp
						(*currentPlayer).setHasLamp(true);
						cout << "Trader: Nice doing business with you!\n";
						cout << "You gained a Lamp!\n";
						//return trader to game
						game1.addMonster(currentHostileMonster);
					}
					else if (choiceTemp == "attack")
					{
						//attack trader
						//return monster to player inventory
						(*currentPlayer).addMonster(selectedMonster);
						//fight till one is dead
						while ((*currentFriendlyMonster).getHealth() > 0 && (*currentHostileMonster).getHealth() > 0)
						{
							int friendlyRandNumber = (rand() % 6 + 1 + (*currentFriendlyMonster).skillLevel());
							int hostileRandNumber = (rand() % 6 + 1 + (*currentHostileMonster).skillLevel());
							if (friendlyRandNumber > hostileRandNumber)
							{
								(*currentHostileMonster).takeDamage(1);
							}
							else if (friendlyRandNumber < hostileRandNumber)
							{
								(*currentFriendlyMonster).takeDamage(1);
							}
							else
							{

							}
						}
						//if player survives
						if ((*currentFriendlyMonster).getHealth() > 0)
						{
							cout << (*currentPlayer).getName() << ", you win!\n";
							cout << "You take the Lamp from his lifeless body!\n";
							//display stats
							cout << "You survive with the following stats:\n";
							(*currentPlayer).displayStats();
							//give lamp
							(*currentPlayer).setHasLamp(true);
							//clean up
							delete currentHostileMonster;
						}
						else
						{
							//set player to dead
							(*currentPlayer).setAlive(false);
						}
					}
					else
					{
						//add monster to player inventory and return trader to game
						cout << "Fair enough, that offer still stands though!\n";
						(*currentPlayer).addMonster(selectedMonster);
						game1.addMonster(currentHostileMonster);
					}

				}
				else
				{
					//if they have no monsters of any tyme
					cout << "You have nothing of interest to me, come back once you do!\n";
					//return trader to game
					game1.addMonster(currentHostileMonster);
				}
			}
			else if ((*currentHostileMonster).getType() == "Skeletor")
			{
				//check that player has evolved monster
				if ((*currentPlayer).hasEvolvedMonster())
				{
					//set friendly moster to evolved monster
					currentFriendlyMonster = (*currentPlayer).m_evMon;
					//display stats
					(*currentFriendlyMonster).displayStats();

					cout << "YOU FIGHT YOUR ENEMY!!\n";
					//fight untill dead
					while ((*currentFriendlyMonster).getHealth() > 0 && (*currentHostileMonster).getHealth() > 0)
					{
						int friendlyRandNumber = (rand() % 6 + 1 + (*currentFriendlyMonster).skillLevel());
						int hostileRandNumber = (rand() % 6 + 1 + (*currentHostileMonster).skillLevel());
						if (friendlyRandNumber > hostileRandNumber)
						{
							(*currentHostileMonster).takeDamage(1);
						}
						else if (friendlyRandNumber < hostileRandNumber)
						{
							(*currentFriendlyMonster).takeDamage(1);
						}
						else
						{

						}
					}
					//if player survived
					if ((*currentFriendlyMonster).getHealth() > 0)
					{
						//tell player he won
						cout << (*currentPlayer).getName() << ", you win!\n";
						break;
					}
					else
					{
						//set player to dead
						(*currentPlayer).setAlive(false);
					}
				}
				else
				{
					//if doesnt have an evolved monster
					cout << "You do not have an evolved Monster!\n";
					cout << "Your position will be randomised!\n";
					//randomise location
					game1.randomiseLocation(currentPlayer);

				}

				
			}


		}
		else
		{
			//if there are no monsters at the player location
			cout << "There are no monsters at this location!\n";
		}


		
		
		//check if player is dead
		if (!((*currentPlayer).getAlive()))
		{
			cout << (*currentPlayer).getName() << ", you have died!\n";
			cout << "You lose!\n";
			break;
		}

		//if there are two players, switch whose turn it is
		if (playeNum == 2)
		{
			if (currentPlayer == game1.m_player1)
			{
				currentPlayer = game1.m_player2;
			}
			else
			{
				currentPlayer = game1.m_player1;
			}
			cout << (*currentPlayer).getName() << ", its your turn!\n";
		}

		
		
	}
	
	

	system("pause");
	return 0;
}