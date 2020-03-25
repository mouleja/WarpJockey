/******************************************************************************
** Program name: Ship.hpp
** Author: Jason Moule
** Assignment: Final Project -  CS162-400-W19
** Date: 3/10/19
** Description: Ship class used in Warp Jockey game
**	Ship stores player data and inventory
******************************************************************************/

#include "Ship.hpp"

// static constants TUNABLE
int Ship::MAX_HULL = 100;	// maximum hull strength
int Ship::CARGO = 250;		// total cargo space in ship 
vector<int> Ship::SIZE = { 1, 1, 5, 5, 10 };	// cargo size of each inventory type
vector<string> Ship::DESC = { "Food", "Fuel", "Trade Goods", "Raw Ore", "Fuel Processor" };

// inventory reference = { Food, Fuel, Trade Goods, Raw Ore, Fuel Processor } 

Ship::Ship()
{
	space = nullptr;		// assign in main
	inventory = { 20, 75, 0, 0, 0};	// Starting inventory TUNABLE
	hull = 50;
	cash = 500;
	turn = 0;
    lastMsg = "It's your first day as a warp jockey!";
}


Ship::~Ship()
{
}

Space * Ship::GetSpace() const
{
	return space;
}

void Ship::SetSpace(Space * s)
{
	space = s;
}

int Ship::GetInventory(int index) const
{
	return inventory[index];
}

void Ship::ChangeInventory(int index, int qty)
{
	inventory[index] += qty;
}

int Ship::GetHull() const
{
	return hull;
}

void Ship::ChangeHull(int amount)
{
	hull += amount;
}

int Ship::GetCash() const
{
	return cash;
}

void Ship::ChangeCash(int amount)
{
	cash += amount;
}

int Ship::GetTurn() const
{
	return turn;
}

void Ship::AddDay()
{
	++turn;
}

int Ship::GetCargo() const
{
    int used = 0;
    for (unsigned int i = 0; i < inventory.size(); ++i)
    {
        used += inventory[i] * Ship::SIZE[i];   // total used space of each item type
    }
    return used;
}

int Ship::GetAvailableCargo() const
{
    return ( Ship::CARGO - this->GetCargo() );
}

string Ship::GetLastMsg() const
{
    return lastMsg;
}

void Ship::SetLastMsg(string msg)
{
    lastMsg = msg;
}
