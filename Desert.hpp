/******************************************************************************
** Program name: Desert.hpp
** Author: Jason Moule
** Assignment: Final Project -  CS162-400-W19
** Date: 3/10/19
** Description: Child class of Space used in Warp Jockey game
**	Desert represents space with a desert planet in it
******************************************************************************/

#ifndef DESERT_HPP_JM
#define DESERT_HPP_JM

#include "Space.hpp"

class Desert : public Space
{
public:
	Desert() : Space('#')
	{
	}

	~Desert()
	{
	}

	// Virtual methods

	// return char vector of available commands
	virtual std::vector<char> GetChoices();

	// return string vector of descriptions of each choice available (in same order)
	virtual std::vector<std::string> GetOptions();

	// Do mini-game (if applicable) or movement based on choice made, return new space or `this`
	virtual int DoOption(char c);

	// Do any actions required when user enters this space, return string with status
	virtual std::string GetStatusMsg();
};

#endif