/******************************************************************************
** Program name: WarpJockey.hpp
** Author: Jason Moule
** Assignment: Final Project -  CS162-400-W19
** Date: 3/10/19
** Description: Warp Jockey game 
**	header for includes, usings, prototypes, global constants, etc
******************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <ctime>
#include <cstdlib>

#include "iohelper.hpp"	// mostly validators and menu programs
#include "City.hpp"		// space type classes
#include "Desert.hpp"
#include "Empty.hpp"
#include "Gas.hpp"
#include "Jungle.hpp"
#include "Warp.hpp"
#include "Ship.hpp"		// ship (player) class

// global constants
const int ROWS = 10;
const int COLS = 10;
const int FOOD_PER_TURN = 2;    // Tunable constants
const int FUEL_PER_MOVE = 4;
const int GOAL = 3000;
const int TURN_LIMIT = 90;

// function prototypes
void game();

void deleteMap(Space * map);

void displayUI(Space * map, Ship * ship);

void intro();
Space* makeNewMap();
Space * getClearSpace(Space * head);
void placeShip(Space* map, Ship* ship);
void displayUI(Space * map, Ship * ship);
vector<string> updateMap(Space* map, Ship* ship);
vector<string> updateStatsStr(Ship * ship);
vector<string> getLegend();
vector<string> updateInvStr(Ship * ship);
bool processCommand(char command, Space * &map, Ship * ship, bool &endGame, bool &pastWin);