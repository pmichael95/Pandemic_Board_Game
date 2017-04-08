#include "ConcreteStrategy.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------ DRIVE FERRY CLASS ------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Player can move to a connecting city
bool DriveFerry::execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer)
{
	//Finds the pawn which is to be moved, handles Dispatcher special case
	int playerOfPawn;
	pawnSelection(playerList, activePlayer, playerOfPawn);

	cout << "Drive / Ferry Selected: Where would you like to go? " << endl;
	int newLocation;
	vector<CityNode*> connections = playerList[playerOfPawn]->getPawn()->getConnections();

	// Check for possible nearby cities 
	for (int i = 0; i < connections.size(); i++) {
		cout << connections[i]->getName() << " (" << i << ")" << endl;
	}
	//Check input
	if (!getIntInput(newLocation, 0, connections.size())) {
		return false;
	}

	// Change location of the player
	playerList[playerOfPawn]->setPawn(connections[newLocation]);
	cout << "Player "<< playerOfPawn +1 << " is now in " << playerList[playerOfPawn]->getPawn()->getName() << endl << endl;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------ DIRECT FLIGHT CLASS ------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Player can discard a city card to fly directly to that city
bool DirectFlight::execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer)
{
	//Finds the pawn which is to be moved, handles Dispatcher special case
	int playerOfPawn;
	pawnSelection(playerList, activePlayer, playerOfPawn);

	cout << "Direct Flight Selected: Where would you like to go? (To go back to menu enter non-displayed character)" << endl;
	int newLocation;
	vector<CityNode*> connections;
	//go through hand and find city cards and add them to possible connections
	for (int l = 0; l < playerList[activePlayer]->getNumOfCards(); l++)
	{
		if (playerList[activePlayer]->getCard(l)->getType() == "City")
		{
			CityCard *card = dynamic_cast<CityCard*>(playerList[activePlayer]->getCard(l));
			connections.push_back(map->getCity(card->getCity()));
		}
	}

	if (connections.size() == 0)
	{
		cout << "You have no city cards in your hand, You cannot use Direct Flight";
		return false;
	}
	//print out where the player can fly
	for (int k = 0; k < connections.size(); k++) {
		cout << connections[k]->getName() << " (" << k << ")" << endl;
	}

	//check input
	if (!getIntInput(newLocation, 0, connections.size())) {
		return false;
	}

	playerList[playerOfPawn]->setPawn(connections[newLocation]);
	//go through hand to find city card used and remove it
	for (int j = 0; j < playerList[activePlayer]->getNumOfCards(); j++)
	{
		if (playerList[activePlayer]->getCard(j)->getType() == "City")
		{
			if (*playerList[activePlayer]->getCard(j) == playerList[activePlayer]->getPawn()->getName())
			{
				Card* card = playerList[activePlayer]->removeCard(j);
				delete card;
				card = nullptr;
			}
		}
	}

	cout << "Player " << playerOfPawn + 1 << " is now in " << playerList[playerOfPawn]->getPawn()->getName() << endl << endl;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------ CHARTER FLIGHT CLASS ------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Player can discard a card matching their current city and move anywhere
bool CharterFlight::execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer)
{
	//Finds the pawn which is to be moved, handles Dispatcher special case
	int playerOfPawn;
	pawnSelection(playerList, activePlayer, playerOfPawn);

	cout << "Charter Flight Selected: Where would you like to go?" << endl;
	int newLocation;
	int cardIndex;
	// Checks hand for City Card
	if (cardIndex = playerList[activePlayer]->checkifPlayerHasCard(playerList[playerOfPawn]->getPawn()->getName()) != -1) {
		//List all cities
		for (int k = 0; k < NUM_OF_CITIES; k++)
		{
			string name = map->getCityList()->at(k)->getName();
			cout << name << " (" << k << ")\t";
			if (k % 12 == 11)
			{
				cout << endl;
			}
		}

		//Check input
		if (!getIntInput(newLocation, 0, NUM_OF_CITIES)) {
			return false;
		}

		// Change the location of the player
		playerList[playerOfPawn]->setPawn(map->getCityList()->at(newLocation));

		//remove card
		Card* card = playerList[activePlayer]->removeCard(cardIndex);
		delete card;
		card = nullptr;

		
		cout << "Player " << playerOfPawn + 1 << " is now in " << playerList[playerOfPawn]->getPawn()->getName() << endl << endl;
		return true;
	}
	// Player does not have card in hand
	else
	{
		cout << "Sorry, Charter Flight is not possible, you don't have the card for the city you wish to move from." << endl;
		return false;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------ SHUTTLE FLIGHT CLASS ------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//A Player in a city with a Research Station can move to any other city with a Research Station
bool ShuttleFlight::execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer)
{
	//Finds the pawn which is to be moved, handles Dispatcher special case
	int playerOfPawn;
	pawnSelection(playerList, activePlayer, playerOfPawn);

	// Check whether player is at a research station
	if (!playerList[playerOfPawn]->getPawn()->hasResearchStation()) {
		cout << "Pawn is not currently at a research station! " << endl;
		return false;
	}

	//Special Case: If player is an operations expert they have the option to go anywhere
	if (*playerList[activePlayer] == OPERATIONS) {
		//List all cities
		cout << "Shuttle Flight Selected: Where would you like to go?" << endl;
		for (int k = 0; k < NUM_OF_CITIES; k++)
		{
			string name = map->getCityList()->at(k)->getName();
			cout << name << " (" << k << ")\t";
			if (k % 12 == 11)
			{
				cout << endl;
			}
		}
		//Check input
		int newLocation;
		if (!getIntInput(newLocation, 0, NUM_OF_CITIES)) {
			return false;
		}

		// Change the location of the player
		playerList[playerOfPawn]->setPawn(map->getCityList()->at(newLocation));
		return true;
	}


	//Default Case///////////////////////////////////
	cout << "Shuttle Flight Selected: Where would you like to go? " << endl;
	vector<CityNode*>* cityList = map->getCityList();
	vector<CityNode*> researchStation;

	// Goes through every city and check if it has a research station
	for (int i = 0; i < cityList->size(); i++) {
		if (cityList->at(i)->hasResearchStation() && cityList->at(i) != playerList[activePlayer]->getPawn()) {
			researchStation.push_back(cityList->at(i));
		}
	}

	// Print out list of cities with research station
	for (int i = 0; i < researchStation.size(); i++) {
		cout << researchStation[i]->getName() << " (" << i << ")" << endl;
	}

	//Check input
	int newLocation;
	if (!getIntInput(newLocation, 0, researchStation.size())) {
		return false;
	}

	// Move Player to the City 
	playerList[playerOfPawn]->setPawn(researchStation[newLocation]);
	cout << "Player " << playerOfPawn + 1 << " is now in " << playerList[playerOfPawn]->getPawn()->getName() << endl << endl;
	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------ DISPATCHER MOVE CLASS ------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Dispatcher ONLY, can move any players pawn to the location of another players pawn.
bool DispatcherMovement::execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer)
{
	if (!(*playerList[activePlayer] == DISPATCHER)) {
		cout << "You are not the Dispatcher and cannot make this move." << endl;
		return false;
	}
	//Active Player is the Dispatcher
	else {
		//Finds the pawn which is to be moved
		int playerOfPawn;
		pawnSelection(playerList, activePlayer, playerOfPawn);

		//Asks which player to move the pawn to
		cout << "To which player would you like to move player " << playerOfPawn + 1 << "'s pawn?" << endl;
		for (int i = 0; i < playerList.size(); i++) {
			if (i != playerOfPawn) {
				cout << "- Player " << i + 1 << endl;
			}
		}

		//Checks for valid input
		int otherPlayer;
		if (!getIntInput(otherPlayer, 1, playerList.size() + 1)) {
			return false;
		}
		otherPlayer--;

		//Move Player
		playerList[playerOfPawn]->setPawn(playerList[otherPlayer]->getPawn());
		cout << "Player " << playerOfPawn + 1 << " is now in " << playerList[playerOfPawn]->getPawn()->getName() << endl << endl;
		return true;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------ BUILD RESEARCH STATION CLASS ------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Player can build a research station in their current city if they discard the matching city card.
bool BuildResearchStation::execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer)
{
	cout << "Build a Research Station Selected" << endl;

	//Special Case: Operations Expert Players can build without discarding a matching city card
	if (*playerList[activePlayer] == OPERATIONS){
		if (markers->useResearchStation()) {
			playerList[activePlayer]->getPawn()->addResearchStation();
			cout << "Research Station Added! ";
			return true;
		}
		else {
			cout << "No more Research Stations to be built." << endl;
			return false;
		}
	}
	//Default Case: Player discards a matching city card to build a research station
	else {
		//Check if player has the card for the city they are in
		int index;
		if (index = playerList[activePlayer]->checkifPlayerHasCard(playerList[activePlayer]->getPawn()->getName()) != -1) {
			//Build a research station
			if (markers->useResearchStation()) {
				playerList[activePlayer]->getPawn()->addResearchStation();
				cout << "Research Station Added! ";
				Card* card = playerList[activePlayer]->removeCard(index);
				delete card;
				card = nullptr;
				return true;
			}
			//No research station markers left
			else {
				cout << "No more Research Stations to be built." << endl;
				return false;
			}
		}
		//Player does not have the card for the city they are in
		else {
			cout << "You cannot build a Research Station here, you do not have a matching card." << endl;
			return false;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------ DISCOVER CURE CLASS ------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//By Discarding 5 cards of the same color, the player can cure the disease of that color
bool DiscoverCure::execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer)
{
	//Check if player is at a city with a research station.
	if (playerList[activePlayer]->getPawn()->hasResearchStation()) {
		int numberToCure;
		//Special Case: Scientist only need 4 cards to cure
		if (*playerList[activePlayer] == SCIENTIST) {
			numberToCure = NUM_OF_CARDS_TO_CURE_FOR_SCIENTIST;
		}
		//Default Case: Players need 5 cards to cure
		else {
			numberToCure = NUM_OF_CARDS_TO_CURE;
		}

		//Display Player Card Options
		cout << "Please select " << numberToCure << " cards of the same color." << endl;
		playerList[activePlayer]->displayPlayerCardOptions();

		//Player selects cards for cure
		int count[NUM_OF_DISEASES] = { 0 };
		int* answer = new int[numberToCure];
		fill_n(answer, numberToCure, -1);
		for (int i = 0; i < numberToCure; i++) {
			
			//Checks for valid input
			if (!getIntInput(answer[i], 0, playerList[activePlayer]->getNumOfCards())) {
				return false;
			}
			
			//Check if Valid Choice
			for (int j = 0; j < numberToCure; j++) {
				//Check that card has not already been selected
				if (i != j && answer[i] == answer[j]) {
					cout << "That card has already been selected, you need to start over." << endl;
					return false;
				}
				//Check that a city card has been selected
				if (playerList[activePlayer]->getCard(answer[j])->getType() != "City") {
					cout << "That is not a city card" << endl;
					return false;
				}
			}
			count[dynamic_cast<CityCard*>(playerList[activePlayer]->getCard(answer[i]))->getColor()]++;
		}
		
		//Check if requirements have been met and cure 
		for (int i = 0; i < NUM_OF_DISEASES; i++) {
			if (count[i] == numberToCure) {
				
				//Discard Cards
				Card* card;
				for (int j = 0; j < numberToCure; j++) {
					card = playerList[activePlayer]->removeCard(answer[j]);
					delete card;
					card = nullptr;
				}
				
				//Cure Disease
				markers->cureDiseaseUpdateMarker(static_cast<InfectType>(i));
				cout << "The " << infectTypeEnumToString(static_cast<InfectType>(i)) << " disease has been cured." << endl;
				return true;
			}
		}
		cout << "Cannot cure any disease with these cards." << endl;
		return false;
	}
	//Player is not at a city with a research station
	else {
		cout << "You must be at a research station to cure a disease!" << endl;
		return false;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------ TREAT DISEASE CLASS ------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Player removes cubes of a disease from a city
bool TreatDisease::execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer)
{
	//Player chooses which disease to treat
	for (int i = 0; i < NUM_OF_DISEASES; i++) {
		cout << i << ") " << infectTypeEnumToString(static_cast<InfectType>(i)) << endl;
	}
	int answer;

	//Checks for valid input
	if (!getIntInput(answer, 0, NUM_OF_DISEASES)) {
		return false;
	}

	InfectType infection = static_cast<InfectType>(answer);
	CityNode* city = playerList[activePlayer]->getPawn();

	//If Disease is cured or Player is Medic - remove all cubes of color
	if (markers->getCureMarker(infection) == cured || *playerList[activePlayer] == MEDIC) {
		int cubesToRemove = city->getInfectionLevel(infection);
		for (int i = 0; i < cubesToRemove; i++) {
			city->reduceInfectionLevel(infection);
			markers->addDiseaseCube(infection);
		}
		checkifDiseaseNowEradicated(markers, infection);
		cout << "All blocks of " << infectTypeEnumToString(infection) << " disease have been removed." << endl;
		return true;
	}
	//If Disease is not cured - remove one cube of color
	else if (city->getInfectionLevel(infection) > 0) {
		city->reduceInfectionLevel(infection);
		markers->addDiseaseCube(infection);
		checkifDiseaseNowEradicated(markers, infection);
		cout << "One block of " << infectTypeEnumToString(infection) << " disease has been removed." << endl;
		return true;
	}
	//No cubes in city to remove
	else {
		cout << "No infection of color " << infectTypeEnumToString(infection) << " here to cure." << endl;
		return false;
	}
}

void TreatDisease::checkifDiseaseNowEradicated(Markers* markers, InfectType infection)
{
	if (markers->getCureMarker(infection) == cured) {
		//If there are no more cubes on the map the disease is eradicated
		if (markers->getNumOfDiseaseCubes(infection) == NUM_OF_DISEASE_CUBES_PER_TYPE) {
			markers->eradicateDiseaseUpdateMarker(infection);
			cout << infectTypeEnumToString(infection) << " Disease has now been eradicated!" << endl;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------ SHARE KNOWLEDGE CLASS --------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Player can give other player a card if in the same city, and the card matches the city
bool ShareKnowledge::execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer)
{
	int cardToPass = -1;
	int otherPlayer = -1;
	cout << "Share Knowledge Selected." << endl;

	//Ask who they would like to share knowledge with
	cout << "Which player would you like to share knowlege with?" << endl;
	for (int i = 0; i < playerList.size(); i++) {
		if (i != activePlayer) {
			cout << "- Player " << i + 1 << endl;
		}
	}

	//Checks for valid input
	if (!getIntInput(otherPlayer, 1, playerList.size() + 1)) {
		return false;
	}
	otherPlayer--;

	// Checks if players are in the same city
	if (playerList[activePlayer]->getPawn() != playerList[otherPlayer]->getPawn()) {
		cout << "Sorry, you and the other player are not in the same city, you cannot share a card." << endl;
		return false;
	}

	//Special Case: Researcher can give any card
	if (*playerList[activePlayer] == RESEARCHER) {
		cout << "Please select the card to pass." << endl;
		playerList[activePlayer]->displayPlayerCardOptions();
		//Checks for valid input
		if (!getIntInput(cardToPass, 0, playerList[activePlayer]->getNumOfCards())) {
			return false;
		}
		//If approved Transfer card
		if (getAnotherPlayersApproval(otherPlayer + 1)) {
			transferCard(cardToPass, playerList[activePlayer], playerList[otherPlayer], playerDeck);
		}
		return true;
	}
	//Special Case: Player can take any card from the Researcher
	else if (*playerList[otherPlayer] == RESEARCHER) {
		//Display Player Card Options
		cout << "Please select the card to pass." << endl;
		playerList[otherPlayer]->displayPlayerCardOptions();
		//Checks for valid input
		if (!getIntInput(cardToPass, 0, playerList[otherPlayer]->getNumOfCards())) {
			return false;
		}
		//If approved Transfer card
		if (getAnotherPlayersApproval(otherPlayer + 1)) {
			transferCard(cardToPass, playerList[otherPlayer], playerList[activePlayer], playerDeck);
			return true;
		}
	}
	//Default Case: Can pass the card that matches the city location
	else {

		// Searches active players hand for City cards that match location
		if (int i = playerList[activePlayer]->checkifPlayerHasCard(playerList[activePlayer]->getPawn()->getName()) != -1) {
			cout << "You have the card for this city, you may pass it." << endl;
			//If approved Transfer card
			if (getAnotherPlayersApproval(otherPlayer + 1)) {
				transferCard(i, playerList[activePlayer], playerList[otherPlayer], playerDeck);
				return true;
			}
		}
		//Searches other players hand for City cards that match location
		else if (int i = playerList[otherPlayer]->checkifPlayerHasCard(playerList[activePlayer]->getPawn()->getName()) != -1) {
			cout << "The other player has the card for this city, they may pass it." << endl;
			//If approved Transfer card
			if (getAnotherPlayersApproval(otherPlayer + 1)) {
				transferCard(i, playerList[otherPlayer], playerList[activePlayer], playerDeck);
				return true;
			}
		}
		//No cards matching location found
		else {
			cout << "Neither of you have the card for " << playerList[activePlayer]->getPawn()->getName() << " and so cannot share." << endl;
			return false;
		}
	}
	//The transfer was rejected
	cout << "The other player has rejected your request" << endl;
	return false;
}

//Transfers the card from one players hand to another and checks player hand size
void ShareKnowledge::transferCard(int cardToPass, Player* fromPlayer, Player* toPlayer, Deck* playerDeck) {
	Card* card = fromPlayer->removeCard(cardToPass);
	toPlayer->addCard(card);
	//Check if players' hand of cards is too large
	if (toPlayer->getNumOfCards() > MAX_HAND_SIZE) {
		discardPlayerCard(toPlayer, playerDeck);
	}
	cout << "You have successfully passed the card." << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------ SHOW REFERENCE CARD CLASS ------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Player views Reference Card description
bool ShowRefCard::execute(GameMap * map, Markers * markers, vector<Player*> playerList, Deck * playerDeck, Deck * infectionDeck, int activePlayer)
{
	system("cls");
	ReferenceCard refCard;
	cout << refCard.print() << endl;
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------ TAKE EVENT CARD CLASS ------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TakeEventCard::execute(GameMap * map, Markers * markers, vector<Player*> playerList, Deck * playerDeck, Deck * infectionDeck, int activePlayer)
{
	if (!(*playerList[activePlayer] == PLANNER)) {
		cout << "You are not the Contingency Planner and cannot make this move." << endl;
		return false;
	}
	//Active Player is the Planner
	else {
		deque<Card*> discardPile = playerDeck->getDiscardPile();
		//check if there are any cards to pick from
		if (discardPile.size() == 0) {
			cout << "There are no event cards in the discard pile." << endl;
			return false;
		}
		else {
			//Display choices
			cout << "Which card would you like to take?" << endl;
			for (int i = 0; i < discardPile.size(); i++) {
				cout << i << ") " << discardPile[i]->print() << endl;
			}
			//Get valid input
			int answer;
			if (!getIntInput(answer, 0, discardPile.size())) {
				return false;
			}
			else{
				//take card
				playerList[activePlayer]->addExtraPlannerCard(playerDeck->getDiscardedCard(answer));
				cout << "Contingency Planner took an event card, this card does not count against your hand limit." << endl;
				return true;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------DO NOTHING CLASS ------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Keeps program from crashing when player chooses not to act
bool DoNothing::execute(GameMap * map, Markers * markers, vector<Player*> playerList, Deck * playerDeck, Deck * infectionDeck, int activePlayer)
{
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------DRAW CARD CLASS ------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool DrawCard::execute(GameMap * map, Markers * markers, vector<Player*> playerList, Deck * playerDeck, Deck * infectionDeck, int activePlayer)
{
	//Draw a card
	Card* card = playerDeck->drawFromTop();
	cout << "\nPlayer " << activePlayer + 1 << " has drawn a " << card->getType() << " card" << endl;

	//Check if epidemic card
	if (card->getType() == "Epidemic") {
		epidemicCardActions(map, markers, playerList, infectionDeck);
		delete card;
	}
	//If a city or event card -> Add to hand
	else {
		playerList[activePlayer]->addCard(card);
		cout << "The card has been added to player " << activePlayer + 1 << "'s hand" << endl;
		cout << "\t- " << card->print() << endl;

		//Check if players' hand of cards is too large
		if (playerList[activePlayer]->getNumOfCards() > MAX_HAND_SIZE) {
			discardPlayerCard(playerList[activePlayer], playerDeck);
		}
	}
	return true;
}

//called when player draws an epidemic card
void DrawCard::epidemicCardActions(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* infectionDeck)
{
	cout << "\n---------An Epidemic Card has been Pulled!!!-----------" << endl << endl;
	//Increase infection Rate
	markers->increaseInfectRate();
	cout << "Infection Rate has increased to " << markers->getInfectionRate() << endl;

	//Add 3 cubes to a city or until an outbreak occurs
	InfectionCard* card = dynamic_cast<InfectionCard*>(infectionDeck->drawFromBottom());
	cout << "Infection Card drawn - " << card->print() << endl;
	CityNode* city = map->getCity(card->getCity());
	InfectType infection = card->getColor();
	infectionDeck->discard(card);
	int outbreakCounterBefore = markers->getOutbreakCounter();

	for (int i = 0; i < EPIDEMIC_INFECTION || markers->getOutbreakCounter() != outbreakCounterBefore; i++) {
		infectCity(city, infection, vector<string>(), markers, playerList);
	}

	//Ask event card////////////////////////////////////////////////////

	//Reshuffle discard pile and add to top of draw pile
	infectionDeck->discardToDraw();
	cout << "The infection deck discard pile has been shuffled and added to the top of the draw pile." << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------ INFECT CLASS ------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Infect::execute(GameMap * map, Markers * markers, vector<Player*> playerList, Deck * playerDeck, Deck * infectionDeck, int activePlayer)
{
	InfectionCard* card = dynamic_cast<InfectionCard*>(infectionDeck->drawFromTop());
	if (markers->getCureMarker(card->getColor()) != eradicated) {
		cout << "- " << card->print() << endl;
		infectCity(map->getCity(card->getCity()), card->getColor(), vector<string>(), markers, playerList);
		cout << endl;
	}
	infectionDeck->discard(static_cast<Card*>(card));
	return true;
}
