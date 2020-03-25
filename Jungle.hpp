/******************************************************************************
** Program name: Jungle.hpp
** Author: Jason Moule
** Assignment: Final Project -  CS162-400-W19
** Date: 3/10/19
** Description: Child class of Space used in Warp Jockey game
**	Jungle represents space with a jungle planet in it
******************************************************************************/

#ifndef JUNGLE_HPP_JM
#define JUNGLE_HPP_JM

#include "Space.hpp"

class Jungle : public Space
{
public:
	Jungle() : Space('&')
	{
	}

	~Jungle()
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