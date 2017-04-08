#include "InputOutput.h"



//Reads in input and handles boundary cases
//Returns a bool if input was valid or not
bool getIntInput(int & variable, int lowerbound, int upperbound)
{
	if (!(cin >> variable) || variable < lowerbound || variable > upperbound)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input, try again" << endl;
		return false;
	}
	return true;
}

bool getAnotherPlayersApproval(int otherPlayer)
{
	// Get other player's approval
	cout << "\nPlayer " << otherPlayer << " , do you approve this action? (y/n)" << endl;
	char answer;
	//Checks for valid input
	while (!(cin >> answer))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input, try again" << endl;
	}

	//If approved Transfer card
	if (answer == 'y' || answer == 'Y') {
		return true;
	}
	else {
		return false;
	}
}



// Pause Game Function
void pause()
{
	char key;
	cout << "\nReady to continue? (Enter any key to continue.)" << endl;
	cin >> key;
}