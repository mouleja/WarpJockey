/******************************************************************************
** Program name: Space.hpp
** Author: Jason Moule
** Assignment: Final Project -  CS162-400-W19
** Date: 3/10/19
** Description: Abstract base class for spaces used in Warp Jockey game
**	spaces are linked to each thru left, right, up, down pointers
** NOTE: No implementation file, just this header file
******************************************************************************/

#ifndef SPACE_HPP_JM
#define SPACE_HPP_JM

#include <string>
#include <vector>

class Space
{
protected:
	Space *left, *right, *up, *down;
	char type;
public:
	Space(char t) : left(nullptr), right(nullptr), up(nullptr), down(nullptr), type(t)
	{
	}

	virtual ~Space()
	{
	}

	// Getters and Setters

	Space* GetLeft() const
	{
		return left;
	}

	Space* GetRight() const
	{
		return right;
	}

	Space* GetUp() const
	{
		return up;
	}

	Space* GetDown() const
	{
		return down;
	}

	void SetLeft(Space* space)
	{
		left = space;
	}

	void SetRight(Space* space)
	{
		right = space;
	}

	void SetUp(Space* space)
	{
		up = space;
	}

	void SetDown(Space* space)
	{
		down = space;
	}

	void ReplaceSpace(Space *space)
	{
		space->SetUp(up);
		space->SetDown(down);
		space->SetLeft(left);
		space->SetRight(right);
		if (up) { up->SetDown(space); }
		if (down) {	down->SetUp(space);	}
		if (left) { left->SetRight(space); }
		if (right) { right->SetLeft(space); }
		delete this;
	}

	char GetType() const
	{
		return type;
	}

	// Virtual methods

	// return char vector of available commands
	virtual std::vector<char> GetChoices() = 0; 

	// return string vector of descriptions of each choice available (in same order)
	virtual std::vector<std::string> GetOptions() = 0;	// MUST BE SIZE 5

	// Do mini-game (if applicable) or movement based on choice made, return new space or `this`
	virtual int DoOption(char c) = 0;

	// Do any actions required when user enters this space, return string with status
	virtual std::string GetStatusMsg() = 0;
};

#endif