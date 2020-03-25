/******************************************************************************
** Program name: Warp.hpp
** Author: Jason Moule
** Assignment: Final Project -  CS162-400-W19
** Date: 3/10/19
** Description: Child class of Space used in Warp Jockey game
**	Warp represents space with a warp in it (tells interface to create new map)
******************************************************************************/

#ifndef WARP_HPP_JM
#define WARP_HPP_JM

#include "Space.hpp"

class Warp : public Space
{
public:
	Warp() : Space('@')
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