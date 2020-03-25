/******************************************************************************
** Program name: Jungle.cpp
** Author: Jason Moule
** Assignment: Final Project -  CS162-400-W19
** Date: 3/10/19
** Description: Child class of Space used in Warp Jockey game
**	Jungle represents space with a jungle planet in it
******************************************************************************/

#include "Jungle.hpp"

std::vector<char> Jungle::GetChoices()
{
	return std::vector<char>({ 'w', 'e', 'n', 's', 'g' });
}

std::vector<std::string> Jungle::GetOptions()
{
	return std::vector<std::string>({
		"Go <W>est",
		"Go <E>ast",
		"Go <N>orth",
		"Go <S>outh",
		"<G>ather food and water" });
}

int Jungle::DoOption(char c)
{
    if (c == 'g')   // Gather food and water
    {
        return (rand() % 11 + 10);  // amount of food gathered random in [10..20]
    }
    return 0;
}

std::string Jungle::GetStatusMsg()
{
	return "You have landed at a jungle planet";
}