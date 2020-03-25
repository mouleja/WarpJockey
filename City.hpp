/******************************************************************************
** Program name: City.hpp
** Author: Jason Moule
** Assignment: Final Project -  CS162-400-W19
** Date: 3/10/19
** Description: Child class of Space used in Warp Jockey game
**	City represents space with a civilized planet in it
******************************************************************************/

#ifndef CITY_HPP_JM
#define CITY_HPP_JM

#include "Space.hpp"
using std::vector;

class City : public Space
{
private:
    vector<int> currentPrices;
    vector<int> basePrices;
    int lastPriceCheck;
public:
    City();
	
	~City()
	{
	}

    // static constants
    static const vector<int> MIN_PRICE;
    static const vector<int> MAX_PRICE;
    static const vector<int> DAILY_VAR;

	// Virtual methods

	// return char vector of available commands
	virtual std::vector<char> GetChoices();

	// return string vector of descriptions of each choice available (in same order)
	virtual std::vector<std::string> GetOptions();

	// Do mini-game (if applicable) or movement based on choice made, return new space or `this`
	virtual int DoOption(char c);

	// Do any actions required when user enters this space, return string with status
	virtual std::string GetStatusMsg();

    // City specific methods
    vector<int> GetPrices(int turn);
};

#endif