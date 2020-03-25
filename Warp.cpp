/******************************************************************************
** Program name: Warp.cpp
** Author: Jason Moule
** Assignment: Final Project -  CS162-400-W19
** Date: 3/10/19
** Description: Child class of Space used in Warp Jockey game
**	Warp represents space with a warp in it (tells interface to create new map)
******************************************************************************/

#include "Warp.hpp"

std::vector<char> Warp::GetChoices()
{
	return std::vector<char>({ 'w', 'e', 'n', 's', 'd' });
}

std::vector<std::string> Warp::GetOptions()
{
	return std::vector<std::string>({
		"Go <W>est",
		"Go <E>ast",
		"Go <N>orth",
		"Go <S>outh",
		"Engage Warp <D>rive" });
}

int Warp::DoOption(char c)
{
    return 0;
}

std::string Warp::GetStatusMsg()
{
	return "You are at a warp zone.";
}