#include "CommonLibrary.h"
#include "GameController.h"

#include "MapView.h"
#include "PlayerView.h"
#include "Cards.h"

int main()
{
	GameController game;
	//Welcome Screen
	cout << "                                            _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << endl;
	cout << "                                           |                                                                                                                     |" << endl;
	cout << "                                           |                                                 WELCOME TO PANDEMIC!                                                |" << endl;
	cout << "                                           |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|" << endl << endl;
	cout << "==================================================================================================================================================================================================================" << endl << endl;

	//Request: new or saved game?
	int answer;
	cout << "Would you like to:" << endl;
	cout << "1) Start a new game" << endl;
	cout << "2) Load a saved game" << endl;
	
	//Handle unpredictable answers
	if (!(cin >> answer) || answer < 1 || answer > 2)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input" << endl;
		return 0;
	}
	//Start new game
	if (answer == 1)
		game.initializeNewGame();
	//Load saved game
	else if(answer == 2)
		game.loadGame();

	//GameLoop
	while (true)			//Iteration #2//issue, need to stop immediately if lose/win game//
	{
		game.startRound();
		game.saveGame();

		//Request: continue or quit?
		cout << "The last game round has been saved, would you like to:" << endl;
		cout << "1) Continue" << endl;
		cout << "2) Quit" << endl;
		//Check input
		if (!(cin >> answer) || answer < 1 || answer > 2)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input" << endl;
			answer = 2;
		}
		
		if (answer == 2)
			break;
	}
}