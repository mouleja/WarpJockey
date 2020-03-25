/******************************************************************************
** Program name: Gas.cpp
** Author: Jason Moule
** Assignment: Final Project -  CS162-400-W19
** Date: 3/10/19
** Description: Child class of Space used in Gas Jockey game
**	Gas represents space with a warp in it (tells interface to create new map)
******************************************************************************/

#include "Gas.hpp"

std::vector<char> Gas::GetChoices()
{
	return std::vector<char>({ 'w', 'e', 'n', 's', 'p' });
}

std::vector<std::string> Gas::GetOptions()
{
	return std::vector<std::string>({
		"Go <W>est",
		"Go <E>ast",
		"Go <N>orth",
		"Go <S>outh",
		"<P>rocess gas into fuel" });
}

int Gas::DoOption(char c)
{
    if (c == 'p')   // Process gas into fuel
    {
        return (rand() % 11 + 10);  // return random amount in [10..20]
    }
    return 0;
}

std::string Gas::GetStatusMsg()
{
	return "You are orbiting a gas giant planet";
}