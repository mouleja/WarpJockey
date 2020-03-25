/******************************************************************************
** Program name: City.cpp
** Author: Jason Moule
** Assignment: Final Project -  CS162-400-W19
** Date: 3/10/19
** Description: Child class of Space used in Warp Jockey game
**	City represents space with a civilized planet in it
******************************************************************************/

#include "City.hpp"

const vector<int> City::MIN_PRICE = { 1, 5, 5, 30, 200 };
const vector<int> City::MAX_PRICE = { 3, 10, 50, 50, 200 };
const vector<int> City::DAILY_VAR = { 1, 3, 5, 5, 0 };

City::City() : Space('$')
{
    lastPriceCheck = 0;
    for (unsigned int i = 0; i < MIN_PRICE.size(); ++i) // Genereate planet specific base prices
    {
        basePrices.push_back(MIN_PRICE[i] + rand() % (MAX_PRICE[i] - MIN_PRICE[i] + 1));
    }
    currentPrices = basePrices;
}

std::vector<char> City::GetChoices()
{
	return std::vector<char>({ 'w', 'e', 'n', 's', 'b' });
}

std::vector<std::string> City::GetOptions()
{
	return std::vector<std::string>({
		"Go <W>est",
		"Go <E>ast",
		"Go <N>orth",
		"Go <S>outh",
		"Visit <B>azaar" });
}

int City::DoOption(char c)
{
    return 0;
}

std::string City::GetStatusMsg()
{
	return "You have landed at a civilized planet";
}

vector<int> City::GetPrices(int turn)
{
    if (turn != lastPriceCheck)
    {
        lastPriceCheck = turn;
        for (unsigned int i = 0; i < MIN_PRICE.size(); ++i) // Genereate current prices
        {
            if (DAILY_VAR[i] > 0)            // Add random amount in range [-DV..DV]
            {
                currentPrices[i] = basePrices[i] + (rand() % (2 * DAILY_VAR[i])) - DAILY_VAR[i];
            }
            if (currentPrices[i] < MIN_PRICE[i])            // Bounded by Min / Max
            {
                currentPrices[i] = MIN_PRICE[i];
            }
            else if (currentPrices[i] > MAX_PRICE[i])
            {
                currentPrices[i] = MAX_PRICE[i];
            }
        }
    }
    return currentPrices;
}
