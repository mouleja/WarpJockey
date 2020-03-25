/******************************************************************************
** Program name: Empty.cpp
** Author: Jason Moule
** Assignment: Final Project -  CS162-400-W19
** Date: 3/10/19
** Description: Child class of Space used in Warp Jockey game
**	Empty represents space with no planet or warp in it
******************************************************************************/

#include "Empty.hpp"

std::vector<char> Empty::GetChoices()
{
	return std::vector<char>({ 'w', 'e', 'n', 's', 'q' }) ;
}

std::vector<std::string> Empty::GetOptions()
{
	return std::vector<std::string>( {
		"Go <W>est",
		"Go <E>ast",
		"Go <N>orth",
		"Go <S>outh",
		"<Q>uit" } );
}

int Empty::DoOption(char c)
{
    return 0;
}

std::string Empty::GetStatusMsg()
{
	return "You are floating in space";
}
