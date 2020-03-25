/******************************************************************************
** Program name: Desert.cpp
** Author: Jason Moule
** Assignment: Final Project -  CS162-400-W19
** Date: 3/10/19
** Description: Child class of Space used in Warp Jockey game
**	Desert represents space with a desert planet in it
******************************************************************************/

#include "Desert.hpp"

std::vector<char> Desert::GetChoices()
{
	return std::vector<char>({ 'w', 'e', 'n', 's', 'm' });
}

std::vector<std::string> Desert::GetOptions()
{
	return std::vector<std::string>({
		"Go <W>est",
		"Go <E>ast",
		"Go <N>orth",
		"Go <S>outh",
		"<M>ine raw ore to sell" });
}

int Desert::DoOption(char c)
{
    if (c == 'm')
    {
        return (rand() % 11 + 10);  // return random in [10..20] TUNABLE
    }
    return 0;
}

std::string Desert::GetStatusMsg()
{
	return "You have landed at a desert planet";
}