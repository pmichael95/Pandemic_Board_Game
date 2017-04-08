#include "Strategy.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
//----- Strategy Class ------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////

//Selects which players pawn will be moved. Handles special Dispatcher case
void Strategy::pawnSelection(vector<Player*> playerList, int activePlayer, int &movingPawn)
{
	//Check if the player a dispatcher
	if (*playerList[activePlayer] == DISPATCHER) {
		bool selectionApproved = false;
		while (!selectionApproved) {
			//Ask which pawn they wish to move
			cout << "Which player's pawn would you like to move?" << endl;
			for (int i = 0; i < playerList.size(); i++) {
				if (i != activePlayer) {
					cout << i + 1 << "- Player " << i + 1 << endl;
				}
				else {
					cout << i + 1 << "- Your Pawn " << endl;
				}
			}
			int playerPawn;
			//Checks for valid input
			while (!getIntInput(playerPawn, 1, playerList.size() + 1));

			//If player did not select their own pawn
			if (--playerPawn != activePlayer) {

				//If other Player approves exit the loop
				if (getAnotherPlayersApproval(playerPawn + 1)) {
					movingPawn = playerPawn;
					selectionApproved = true;
				}
				else {
					cout << "The other player has rejected your request" << endl;
				}
			}
			//Player selected themselves
			else {
				selectionApproved = true;
			}
		}
	}
	//Player is not the dispatcher
	else {
		movingPawn = activePlayer;
	}
}



//Called when Player has too many cards in hand
void Strategy::discardPlayerCard(Player* player, Deck* playerDeck)
{
	cout << "\nPlayer " << player->getId() << " has too many cards in hand! Select one to discard:" << endl;
	player->displayPlayerCardOptions();
	int answer;

	// Check input
	while (!getIntInput(answer, 0, player->getNumOfCards())) {}

	// Discard Card
	Card* card = player->removeCard(answer);
	if (card->getType() == "City") {
		delete card;
		card = nullptr;
	}
	else {
		playerDeck->discard(card);
	}
	cout << "Discarding Card\n" << endl;
}

//Adds a disease cube to a city
void Strategy::infectCity(CityNode* city, InfectType infection, vector<string> outbreakHistory, Markers* markers, vector<Player*> playerList)
{
	if (!quarentineCheck(city, playerList, markers->getCureMarker(infection) == cured)) {
		//Check if city can be infected
		if (city->getInfectionLevel(infection) < MAX_CUBES_PER_CITY) {
			//Infect city, add cube of infection color to city
			if (markers->useDiseaseCube(infection)) {
				city->increaseInfectionLevel(infection);
				cout << "A " << infectTypeEnumToString(infection) << " cube has been added to " << city->getName() << endl;
			}
			//All disease cubes used
			else {
				//game over //handled in game controller
				return;
			}
		}
		//Outbreak occurs, city already had three disease cubes of infection color
		//All connecting cities will be infected.
		else {
			//track cities that have had an outbreak this chain.
			outbreakHistory.push_back(city->getName());
			handleOutbreak(city, infection, outbreakHistory, markers, playerList);
		}
	}
	//Quarentine check was true --> don't infect
	else {
		cout << "City is protected" << endl;
	}
	
}


//Checks if city is next to a Quarentine Specialist or a Medic
//Returns true, if city affected by Quarentine Specialist
bool Strategy::quarentineCheck(CityNode * city, vector<Player*> playerList, bool isCured)
{
	
	for (auto const& player : playerList) {
		//Check if a player is a Quarentine expert OR Medic with an cured infection
		if (*player == QUARANTINE || (*player == MEDIC && isCured)) {
			//Checks to see if city to infect matches any connected city
			for (auto const& connectedCity : player->getPawn()->getConnections()) {
				if (city == connectedCity) {
					return true;
				}
			}
			//Checks if city to infect matches current city
			if (player->getPawn() == city) {
				return true;
			}
		}
	}
	//No conflicts
	return false;
}

//Handles Outbreak events
void Strategy::handleOutbreak(CityNode * city, InfectType infection, vector<string> outbreakHistory, Markers* markers, vector<Player*> playerList)
{
	//increase counter and check if it has reached maximum
	markers->increaseOutbreakCounter();
	if (markers->getOutbreakCounter() == MAX_OUTBREAKES) {
		//game over
		//endGame(false, "You have reach Outbreak Level 8 (Crossbone Marker)!");
		return;
	}

	cout << "---------An outbreak has occurred in " << city->getName() << "!!!-----------" << endl;

	//Infect all connected cities.
	vector<CityNode*> connections = city->getConnections();
	for (int i = 0; i < connections.size(); i++) {
		bool match = false;
		//Check if an outbreak has already occured here this chain
		for (int j = 0; j < outbreakHistory.size(); j++) {
			if (connections[i]->getName() == outbreakHistory[j])
			{
				match = true;
			}
		}
		if (!match) {
			infectCity(connections[i], infection, outbreakHistory, markers, playerList);
		}
	}
}