#include "WarpJockey.hpp"

int main()
{
	srand((unsigned int)time(0));
	cout << "\nNOTE: This game designed for 80 wide x 24 high console output." 
		<< endl << endl;

	intro();	// Display Intro and introduction

    char playAgain = 'y';
    while (playAgain == 'y')
    {
        game();     // main game loop

        // End message and play again prompt
        cout << "\n\nThanks for playing Warp Jockey!!" << endl;
        char yesNo[] = { 'y', 'n' };
        playAgain = getChar("\nPlay again? (y/n): ", yesNo, 2);
    }
	return 0;
}

void game()
{
    bool endGame = false, pastWin = false;

	Ship* ship = new Ship();        // setup game
    Space* map = makeNewMap();
    placeShip(map, ship);

    while (!endGame)                // main game loop
    {
        bool goodCommand = false;
        ship->AddDay();
        displayUI(map, ship);
        if (ship->GetTurn() > TURN_LIMIT  && !pastWin)
        {
            cout << endl << endl;
            cout << "It's Day " << ship->GetTurn() << "!  From out of nowhere, a sinister ship "
                << "appears and zaps your ship \nwith an EMP ray.  An enormous thug boards your "
                << "ship and escorts you to the \nother ship.  Sometime later you are dropped off "
                << "at your home planet, with no \nship and 50 cash to your name.\nLooks like it's"
                << " back to the life of a porter for you!!!" << endl << endl;
            endGame = true;
        }
       while (!goodCommand && !endGame) {
            char command = getChar("Please enter command: ", ship->GetSpace()->GetChoices());
            goodCommand = processCommand(command, map, ship, endGame, pastWin);
        }
    }

    // Cleanup memory
    delete ship;
    deleteMap(map);
}

void deleteMap(Space * map)
{
    Space* next = map;
    while (next)         // go through all rows
    {
        Space* nextRow = next->GetDown();
        while (next)    // delete current row
        {
            Space* nextNext = next->GetRight();
            delete next;
            next = nextNext;
        }
        next = nextRow;
    }
}

void intro()
{
	for (int i = 0; i < 24; ++i)	// Clear screen
	{
		cout << endl;
	}

	cout <<
		"       WW      WW                         JJJJJJJ\n" <<
		"      WW      WW                              JJ\n" <<
		"     WW      WW                              JJ\n" <<
		"    WW      WW  AA      RRRR    PPPP        JJ  OOOO  CCCC  K  K    EEEE  Y  Y\n" <<
		"   WW  WW  WW  A A     R  R    P  P        JJ  O  O  C     K  K    E     Y  Y\n" <<
		"  WW  WW  WW  A  A    RRRR    PPPP   JJ   JJ  O  O  C     KKK     EEE   YYYY\n" <<
		" WW  WW  WW  AAAAA   R  R    P      JJ   JJ  O  O  C     K  K    E        Y\n" <<
		"WWWWWWWWWW  A    A  R    R  P      JJJJJJJ  OOOO  CCCC  K    K  EEEE  YYYY\n"
		<< endl;
	cout << "Well, you finally did it.  After years of working the Martian ports watching"
		<< "\nthe warp jockeys come back from their adventures with exotic flora, fauna"
		<< "\ngems and, of course, incredible (often literally) stories, you have decided"
		<< "\nto join their ranks.  Of course, as a porter, your bank account was a little"
		<< "\nlight, so in the time honored tradition, you visited the local loan shark."
		<< "\nYou are now the proud owner of WarpTech 300z Light Cargo Hauler!"
		<< "\n\nOh, and a " << GOAL << " credit debt due in " << TURN_LIMIT 
        << " days under rather severe penalty for"
		<< "\nfailure to pay!!  But oh, the places you'll go!  You quickly hit the nearest"
		<< "\nwarp zone and find yourself in an unknown galaxy (you couldn't afford a "
		<< "\n'predictable resolution' warp drive).  Time to start exploring!!!" << endl << endl;

	getString("Press Enter to continue...");

	cout << "\nSome basics: You require " << FOOD_PER_TURN << " food per turn, if you run out of food, you die!"
		<< "\nMoving takes " << FUEL_PER_MOVE << " fuel per turn. Planet based actions take a turn without"
		<< "\nrequiring fuel. All resources (except Cash) require cargo space, you have"
		<< "\n" << Ship::CARGO << " units of space. The amount of space required per unit is shown in ( )"
		<< "\nin the inventory. All resources can be bought and sold at a City planet bazaar."
		<< "\nOther planets have different options, check `Available Commands` to see them."
		<< "\nYour goal is to raise enough cash (" << GOAL << ") to pay off the loan shark by turn " 
        << TURN_LIMIT << "."
		<< endl << endl;

	getString("Press Enter to continue...");
}

Space * makeNewMap()	// creates a linked 10x10 map and returns top-left (head) space
{
	// First create linked (ROWS x COLS) 2D map of empty spaces
	Space* head = new Empty();	// Head node (DO NOT CHANGE)
	Space* prev = head;

	for (int c = 1; c < COLS; ++c)	// Then first row
	{
		Space* newSpace = new Empty();
		prev->SetRight(newSpace);
		newSpace->SetLeft(prev);
		prev = newSpace;
	}

	Space* above = head;

	for (int r = 1; r < ROWS; ++r)	// Then first column
	{
		Space* newSpace = new Empty();
		above->SetDown(newSpace);
		newSpace->SetUp(above);
		above = newSpace;
	}

	for (int r = 1; r < ROWS; ++r)	// Then rest of cells
	{
		prev = head;
		for (int i = 0; i < r; ++i)	// Get first cell in column
		{
			prev = prev->GetDown();
		}

		above = prev->GetUp();		// The cell above first cell in column

		for (int c = 1; c < COLS; ++c)	// Set up current row
		{
			above = above->GetRight();
			Space* newSpace = new Empty();
			prev->SetRight(newSpace);
			above->SetDown(newSpace);
			newSpace->SetLeft(prev);
			newSpace->SetUp(above);
			prev = newSpace;
		}
	}

	// Second place warp and planets
	vector<Space*> planets ({new Warp(), new City(), new City(), new Desert(), new Desert(),
		new Gas(), new Gas(), new Jungle(), new Jungle()});
	
	while (!planets.empty())
	{
		Space* next = getClearSpace(head);
		next->ReplaceSpace(planets.back());
		planets.pop_back();
	}

	return head;
}

Space* getClearSpace(Space* head)	// returns empty space with 8 empty spaces around it
{
	bool found = false;
	Space* cell = head;

	while (!found)
	{
		cell = head;
		int row = rand() % (ROWS - 2) + 1;	// Don't want planets in first or last row/col
		int col = rand() % (COLS - 2) + 1;	// So range[1..8]

		for (int r = 0; r < row; ++r)
		{
			cell = cell->GetDown();		// Go to random row
		}
		for (int c = 0; c < col; ++c)
		{
			cell = cell->GetRight();	// Go to random col
		}
	
		Space *above = cell->GetUp(), *below = cell->GetDown();
		string types;	// To store types of cell and surrounding cells
		types = { cell->GetType(), cell->GetLeft()->GetType(), cell->GetRight()->GetType(),
			above->GetType(), above->GetLeft()->GetType(), above->GetRight()->GetType(),
			below->GetType(), below->GetLeft()->GetType(), below->GetRight()->GetType() };
		
		//cout << "Debug: types string in getClearSpace: " << types << endl;

		if ((signed int)types.find_first_not_of(' ') == -1)	// Are any types not empty (' ' type)
		{
			found = true;
		}
	}
	return cell;
}

void placeShip(Space * map, Ship * ship)
{
	bool found = false;
    Space* cell = map;

	while (!found)
	{
        cell = map;
        int row = rand() % ROWS;	// Random row & col
        int col = rand() % COLS;

		for (int r = 0; r < row; ++r)
		{
			cell = cell->GetDown();		// Go to random row
		}
		for (int c = 0; c < col; ++c)
		{
			cell = cell->GetRight();	// Go to random col
		}
		if (cell->GetType() == ' ')		// Check for empty cell
		{
			found = true;
		}
	}
	ship->SetSpace(cell);				// Set location of ship
}

void displayUI(Space * map, Ship * ship)
{
	vector<string> mapStrings = updateMap(map, ship);
    vector<string> statsStrings = updateStatsStr(ship);
    vector<string> legend = getLegend();
    vector<string> invStrings = updateInvStr(ship);
    string status = ship->GetSpace()->GetStatusMsg();
    vector<string> commands = ship->GetSpace()->GetOptions();
    string lastMsg = ship->GetLastMsg();
	vector<string> UImaster;

	UImaster.push_back(boxTop(79));
	UImaster.push_back("|" + centerStr("Warp Jockey by Jason Moule", 77) + "|");
    UImaster.push_back("|" + centerStr("", 77) + "|");
    UImaster.push_back("|" + centerStr("Map", 12) + ' ' + centerStr("Legend", 18)
        + ' ' + centerStr("Stats", 17) + ' ' + centerStr("Inventory", 27) + "|");
    UImaster.push_back("|" + boxTop(12) + ' ' + boxTop(18) + ' ' + boxTop(17)
        + ' ' + boxTop(27) + '|');
    for (int i = 0; i < 10; ++i)    // process next 10 lines (map, etc)
    {
        string temp = "||" + mapStrings[i] + "| |" + legend[i] + "| |";
        temp += statsStrings[i] + "| |" + invStrings[i] + "||";
        UImaster.push_back(temp);
    }
    UImaster.push_back("|" + boxTop(12) + ' ' + boxTop(18) + ' ' + boxTop(17)
        + ' ' + boxTop(27) + '|');
    UImaster.push_back("|" + boxTop(49) + " |" + leftJustStr(" Available commands:", 25) + "||");
    UImaster.push_back("||" + leftJustStr(" " + status, 47) + "| |"
        + leftJustStr(" " + commands[0], 25) + "||");
    UImaster.push_back("|" + boxTop(49) + " |" + leftJustStr(" " + commands[1], 25) + "||");
    UImaster.push_back("||" + leftJustStr(" " + lastMsg, 47) + "| |"
        + leftJustStr(" " + commands[2], 25) + "||");
    UImaster.push_back("|" + boxTop(49) + " |" + leftJustStr(" " + commands[3], 25) + "||");
    UImaster.push_back("||" + leftJustStr(" Please enter command:", 47) + "| |" 
        + leftJustStr(" " + commands[4], 25) + "||");
    UImaster.push_back("+" + boxTop(49) + "-" + boxTop(27) + "+");

    for (unsigned int i = 0; i < UImaster.size(); ++i)
    {
        cout << UImaster[i] << endl;
    }
}

vector<string> updateMap(Space * map, Ship * ship)
{
	vector<string> mapStrings;

	for (int r = 0; r < ROWS; ++r)
	{
		Space* current = map;			// Start in Upper-Left
		for (int i = 0; i < r; ++i)
		{
			current = current->GetDown();	// Go down r # of times
		}
		string temp;
		for (int c = 0; c < COLS; ++c)
		{
			if (current == ship->GetSpace())
			{
				temp += '=';					// Add ship symbol to map
			}
			else
			{
				temp += current->GetType();		// Add current type to temp string
			}
			current = current->GetRight();
		}
		mapStrings.push_back(temp);			// Add string to vector
	}
	return mapStrings;
}

vector<string> updateStatsStr(Ship * ship)
{
    vector<string> stats;
    stats.push_back(leftJustStr(" ", 15));
    stats.push_back(leftJustStr(" Day " + rightJustInt(ship->GetTurn(), 3, '0'), 15));
    stats.push_back(leftJustStr(" Cash " + rightJustInt(ship->GetCash(), 5, '0'), 15));
    stats.push_back(leftJustStr(" Cargo " + rightJustInt(ship->GetCargo(), 3, '0') + '/' 
        + std::to_string(Ship::CARGO), 15));
    stats.push_back(leftJustStr(" ", 15));
    stats.push_back(leftJustStr(" ", 15));
    stats.push_back(leftJustStr(" ", 15));
    stats.push_back(leftJustStr(" ", 15));
    stats.push_back(leftJustStr(" ", 15));
    stats.push_back(leftJustStr(" ", 15));
    return stats;
}

vector<string> getLegend()
{
    vector<string> legend;
    legend.push_back(leftJustStr(" ", 16));
    legend.push_back(leftJustStr(" = Your Ship", 16));
    legend.push_back(leftJustStr(" @ Warp", 16));
    legend.push_back(leftJustStr(" $ City Planet", 16));
    legend.push_back(leftJustStr(" % Gas Giant", 16));
    legend.push_back(leftJustStr(" # Desert Planet", 16));
    legend.push_back(leftJustStr(" & Jungle Planet", 16));
    legend.push_back(leftJustStr(" ", 16));
    legend.push_back(leftJustStr(" ", 16));
    legend.push_back(leftJustStr(" ", 16));
    return legend;
}

vector<string> updateInvStr(Ship * ship)
{
    vector<string> inv;
    inv.push_back(leftJustStr(" ", 25));
    for (unsigned int i = 0; i < Ship::SIZE.size(); ++i)
    {
        string cur = " ";   // current line of inventory
        cur += rightJustInt(ship->GetInventory(i), 3);
        cur += " " + Ship::DESC[i] + " (";
        cur += std::to_string(Ship::SIZE[i]) + ")";
        inv.push_back(leftJustStr(cur, 25));
    }
    for (unsigned int i = 0; i < (9 - Ship::SIZE.size()); ++i)
    {
        inv.push_back(leftJustStr(" ", 25));
    }
    return inv;
}

bool processCommand(char command, Space *&map, Ship * ship, bool &endGame, bool &pastWin)
{
    bool goodCommand = false;
    Space* dest = ship->GetSpace();

    if (command == 'n')
    {
        dest = dest->GetUp();
        if (!dest)
        {
            cout << "There is too much dark energy in that direction to travel!" << endl;
        }
        else
        {
            ship->ChangeInventory(0, -FOOD_PER_TURN);
            ship->ChangeInventory(1, -FUEL_PER_MOVE);
            ship->SetSpace(dest);
            goodCommand = true;
            ship->SetLastMsg("You traveled north");
        }
    }
    else if (command == 's')
    {
        dest = dest->GetDown();
        if (!dest)
        {
            cout << "There is too much dark energy in that direction to travel!" << endl;
        }
        else
        {
            ship->ChangeInventory(0, -FOOD_PER_TURN);
            ship->ChangeInventory(1, -FUEL_PER_MOVE);
            ship->SetSpace(dest);
            goodCommand = true;
            ship->SetLastMsg("You traveled south");
        }
    }
    else if (command == 'w')
    {
        dest = dest->GetLeft();
        if (!dest)
        {
            cout << "There is too much dark energy in that direction to travel!" << endl;
        }
        else
        {
            ship->ChangeInventory(0, -FOOD_PER_TURN);
            ship->ChangeInventory(1, -FUEL_PER_MOVE);
            ship->SetSpace(dest);
            goodCommand = true;
            ship->SetLastMsg("You traveled west");
        }
    }
    else if (command == 'e')
    {
        dest = dest->GetRight();
        if (!dest)
        {
            cout << "There is too much dark energy in that direction to travel!" << endl;
        }
        else
        {
            ship->ChangeInventory(0, -FOOD_PER_TURN);
            ship->ChangeInventory(1, -FUEL_PER_MOVE);
            ship->SetSpace(dest);
            goodCommand = true;
            ship->SetLastMsg("You traveled east");
        }
    }
    else if (command == 'q')
    {
        endGame = true;
        goodCommand = true;
    }
    else if (command == 'g')
    {
        ship->ChangeInventory(0, -FOOD_PER_TURN);
        int gathered = ship->GetSpace()->DoOption('g');
        ship->ChangeInventory(0, gathered);
        ship->SetLastMsg("You gathered " + std::to_string(gathered) + " food.");
        while (ship->GetAvailableCargo() < 0)
        {
            --gathered;
            ship->ChangeInventory(0, -1);
            ship->SetLastMsg("You gathered " + std::to_string(gathered) + " food. Cargo Bay Full!");
        }        
        goodCommand = true;
    }
    else if (command == 'm')
    {
        ship->ChangeInventory(0, -FOOD_PER_TURN);
        int mined = ship->GetSpace()->DoOption('m');
        ship->ChangeInventory(3, mined);
        ship->SetLastMsg("You mined " + std::to_string(mined) + " raw ore.");
        while (ship->GetAvailableCargo() < 0)
        {
            --mined;
            ship->ChangeInventory(3, -1);
            ship->SetLastMsg("You mined " + std::to_string(mined) + " raw ore. Cargo Bay Full!");
        }
        goodCommand = true;
    }
    else if (command == 'p')
    {
        if (ship->GetInventory(4) > 0)
        {
            ship->ChangeInventory(0, -FOOD_PER_TURN);
            int gathered = ship->GetSpace()->DoOption('p');
            ship->ChangeInventory(1, gathered);
            ship->SetLastMsg("You processed " + std::to_string(gathered) + " fuel.");
            while (ship->GetAvailableCargo() < 0)
            {
                --gathered;
                ship->ChangeInventory(1, -1);
                ship->SetLastMsg("You processed " + std::to_string(gathered) + " fuel. Cargo Bay Full!");
            }
            goodCommand = true;
        }
        else
        {
            cout << "You need to buy a fuel processor first!" << endl;;
        }
    }
    else if (command == 'd')
    {
        ship->ChangeInventory(0, -FOOD_PER_TURN);
        ship->ChangeInventory(1, -FUEL_PER_MOVE);

        deleteMap(map);
        map = makeNewMap();
        placeShip(map, ship);
        goodCommand = true;
        ship->SetLastMsg("You survived another warp!");
    }
    else if (command == 'b')
    {
        ship->ChangeInventory(0, -FOOD_PER_TURN);
        goodCommand = true;
        City* city = dynamic_cast<City*>(ship->GetSpace());
        bool done = false;
        while (!done)
        {
            cout << "\nWelcome to the Bazaar!  You have " << ship->GetCash() << " cash and "
                << ship->GetAvailableCargo() << " available cargo space." << endl;
            char buySell[] = { 'b', 's', 'l' };
            char choice = getChar("Do you want to <B>uy, <S>ell or <L>eave?", buySell, 3);
            if (choice == 'l')
            {
                done = true;
            }
            else if (choice == 'b')
            {
                vector<string> buyMenu;
                vector<int> buyPrice = city->GetPrices(ship->GetTurn());

                for (unsigned int i = 0; i < buyPrice.size(); ++i)  // Add markup
                {
                    buyPrice[i] += buyPrice[i] / 2; // TUNABLE 50% markup over sell price
                    buyMenu.push_back(Ship::DESC[i] + " (" + std::to_string(buyPrice[i]) + ")");
                }

                int item = displayMenu("What do you want to buy (prices in parentheses)?", buyMenu);
                int qty = getInt(0, Ship::CARGO, "Quantity to buy?");
                int price = qty * buyPrice[item - 1];   // Total cost of purchase
                int cargo = qty * Ship::SIZE[item - 1]; // Total cargo size of purchase
                if (price > ship->GetCash())
                {
                    cout << "Sorry, you don't have enough cash!" << endl;
                }
                else if (cargo > ship->GetAvailableCargo())
                {
                    cout << "Sorry, don't have enough cargo space!" << endl;
                }
                else    // successful purchase
                {
                    ship->ChangeCash(-price);
                    ship->ChangeInventory(item - 1, qty);
                    cout << "You have purchased " << qty << " " << Ship::DESC[item - 1] << endl;
                }
            }
            else if (choice == 's')
            {
                vector<string> sellMenu;
                vector<int> sellPrice = city->GetPrices(ship->GetTurn());

                for (unsigned int i = 0; i < sellPrice.size(); ++i)  // Add markup
                {
                    sellMenu.push_back(Ship::DESC[i] + " (" + std::to_string(sellPrice[i]) + ")");
                }

                int item = displayMenu("What do you want to sell (prices in parentheses)?", sellMenu);
                int myInv = ship->GetInventory(item - 1);
                int qty = getInt(0, myInv, "You have " + std::to_string(myInv) + ", quantity to sell?");
                int price = qty * sellPrice[item - 1];   // Total cash for selling
                
                cout << "You sold " << qty << " " << Ship::DESC[item - 1] << " for $" << price << endl;
                ship->ChangeCash(price);
                ship->ChangeInventory(item - 1, -qty);
            }
        }
        ship->SetLastMsg("You visited the bazaar.");
    }

    // Check end game conditions
    if (ship->GetInventory(0) < 0)  // out of food
    {
        endGame = true;
        cout << "\nYou have gone a full day without any food or water.  You think you can make it"
            << "\none more day.  Unfortunately, you are wrong.  Game over :(" << endl;
        return true;
    }

    if (ship->GetInventory(1) < 0 )   // out of fuel
    {
        endGame = true;
        cout << "\nYou are out of fuel.  You live the rest of your short life here."
            << "\nYou wonder if it was all worth it ..." << endl;
        return true;
    }

    if (ship->GetCash() >= GOAL && !pastWin)    // you have enough cash to win
    {
        char yesNo[] = { 'y', 'n' };
        cout << "\nYou look at your cash and realize that you did it, you have enough to pay the"
            << "\nloan off!  Do you want to wire the money to the loan shark? " << endl;
        char answer1 = getChar("(y/n): ", yesNo, 2);
        if (answer1 == 'y')
        {
            ship->ChangeCash(-GOAL);
            char answer2 = getChar("\nYou are your own boss now!  You are a winner!\nDo want to continue playing? (y/n): ");
            if (answer2 == 'y')
            {
                pastWin = true;
            }
            else
            {
                cout << "\nOkay, you have completed your goal!  Best of luck to you ... Captain!" << endl;
                endGame = true;
            }
        }
    }

    return goodCommand;
}
