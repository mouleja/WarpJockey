/******************************************************************************
** Program name: Ship.hpp
** Author: Jason Moule
** Assignment: Final Project -  CS162-400-W19
** Date: 3/10/19
** Description: Ship class used in Warp Jockey game
**	Ship stores player data and inventory
******************************************************************************/

#include "Space.hpp"
using std::vector;
using std::string;

class Ship
{
private:
	Space* space;			// current space ship is in
	vector<int> inventory;	// quantity of each inventory type we own
	int hull;				// hull strength of ship
	int cash;				// cash money yo
	int turn;				// Number of days you've been at this
    string lastMsg;         // display message of last action

public:
	Ship();
	~Ship();

	// static constants
	static int MAX_HULL;		// maximum hull strength
	static vector<int> SIZE;	// cargo size of each inventory type
    static vector<string> DESC; // Description of each inventory type
	static int CARGO;			// total cargo space in ship

	// Getters and Setters

	Space* GetSpace() const;				// Returns current space ship is in
	void SetSpace(Space* s);				// Change current space
	int GetInventory(int index) const;		// Get quantity of inventory[index]
	void ChangeInventory(int index, int qty);	// Add/subtract qty from inventory[index]
	int GetHull() const;					// Get hull strength
	void ChangeHull(int amount);			// Add/subtract amount from hull
	int GetCash() const;					// Get cash balance
	void ChangeCash(int amount);			// Add/subtract amount from cash
	int GetTurn() const;					// Get turns played
	void AddDay();							// Increment day by one
    int GetCargo() const;                   // Get cargo space used
    int GetAvailableCargo() const;          // Get available cargo space
    string GetLastMsg() const;              // Get displayMsg
    void SetLastMsg(string msg);            // Set displayMsg
};

