#include "CommonLibrary.h"
#include "GameController.h"

int main()
{
	GameController game;
	//Welcome Screen

	//Request: new or saved game?
	int answer;
	cout << "Would you like to:" << endl;
	cout << "1) Start a new game" << endl;
	cout << "2) Load a saved game" << endl;
	cin >> answer;
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
		//save game: game.saveGame();
		//Request: continue or quit?
		cout << "The last game round has been saved, would you like to:" << endl;
		cout << "1) Continue" << endl;
		cout << "2) Quit" << endl;
		cin >> answer;
		//Quit
		if (answer == 2)
			break;
	}
}