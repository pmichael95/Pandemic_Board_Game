#include "GameController.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//----CONSTRUCTOR / DECONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////////////////////////

GameController::GameController() : activePlayer(0) {}

GameController::~GameController() {
	for (int i = 0; i < NUM_OF_PLAYERS; i++) {
		delete players[i];
		players[i] = nullptr;
	}
	delete map;
	map = nullptr;
	delete infectionDeck;
	infectionDeck = nullptr;
	delete playerDeck;
	playerDeck = nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// -----INITIALIZE--------
/////////////////////////////////////////////////////////////////////////////////////////////////////

// Initialize New Game: Creates all the base member for the game
void GameController::initializeNewGame()
{
	//initialize models
	map = new GameMap(MAP_INITIAL_FILE);
	infectionDeck = new Deck(INFECTION_CARD_INITIAL_FILE);
	playerDeck = new Deck(PLAYER_CARD_INITIAL_FILE);

	//Setup starting conditions
	map->getHead()->addResearchStation();
	markers.useResearchStation();

	initializePlayers();
	addEpidemicCards();
	initialInfection();

	pause();
}

// Initialize Players: Initialize n number of players
void GameController::initializePlayers() 
{
	Deck* roleDeck = new Deck(ROLE_CARD_INITIAL_FILE);
	for (int i = 0; i < NUM_OF_PLAYERS; i++) {
		players[i] = new Player(i, new ReferenceCard());
		players[i]->setPawn(map->getHead());
		players[i]->setRole(dynamic_cast<RoleCard*>(roleDeck->drawFromTop()));
		for (int j = 0; j < NUM_OF_STARTING_CARDS_PER_PLAYER; j++) {
			players[i]->addCard(playerDeck->drawFromTop());
		}
	}
	delete roleDeck;
}

// Initial Infection: infect cities on new board game
void GameController::initialInfection() 
{
	for (int k = INITIAL_INFECTION; k > 0; k--) {
		for (int i = 0; i < INITIAL_INFECTION; i++) {
			InfectionCard* card = dynamic_cast<InfectionCard*>(infectionDeck->drawFromTop());
			for (int j = 0; j < k; j++) {
				infectCity(map->getCity(card->getCity()), card->getColor());
			}
			infectionDeck->discard(card);
		}
	}
}

void GameController::addEpidemicCards() 
{
	for (int i = 0; i < NUM_OF_EPIDEMIC_CARDS; i++) {
		Card* card = new EpidemicCard();
		playerDeck->addCard(card);
	}
	playerDeck->shuffleDeck();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// -----SAVE/LOAD--------
/////////////////////////////////////////////////////////////////////////////////////////////////////

// Load game via Serialization
void GameController::loadGame()
{ 
	cout << "Restoring saved game..." << endl;
	// Create and input archive
	std::ifstream ifs(SAVED_MAP_FILE);
	boost::archive::text_iarchive ar(ifs);
	ar & markers & map & infectionDeck & playerDeck & players;
	ifs.close();
}

// Same game via Serialization
void GameController::saveGame()
{
	cout << "Saving game..." << endl;
	// Create and input archive
	std::ofstream ofs(SAVED_MAP_FILE);
	boost::archive::text_oarchive ar(ofs);
	ar & markers & map & infectionDeck &playerDeck & players;
	ofs.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// -----GAME ROUND--------
/////////////////////////////////////////////////////////////////////////////////////////////////////

void GameController::startRound()
{
	for (int i = 0; i < NUM_OF_PLAYERS; i++) {
		//Declare player order
		system("cls");
		cout << "Player " << activePlayer + 1 << "'s turn starts now." << endl << endl;
		pause();

		phase1_Actions();	  // Do Phase 1: Player 4 turns
		phase2_DrawCards();	  // Do Phase 2: Draw 2 cards
		phase3_Infects();	  // Do Phase 3: Infect the cities
		switchPlayers();
	}
	system("cls");

	// Updates the map and display all models
	mapDisplay.updateMap(map->getCityList());
	mapDisplay.printMap(&markers);

	for (int i = 0; i < NUM_OF_PLAYERS; i++) {
		playerDisplay.printPlayerDisplay(players[i]);
	}
}

// Switch Player Function
void GameController::switchPlayers()
{	activePlayer = (activePlayer + 1) % NUM_OF_PLAYERS;	}

// Pause Game Function
void GameController::pause()
{
	char key;
	cout << "\nReady to continue? (Enter any key to continue.)" << endl;
	cin >> key;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
// -----PHASE 1--------
/////////////////////////////////////////////////////////////////////////////////////////////////////

void GameController::phase1_Actions()
{
	int i = 0;
	while(i < NUM_OF_ACTIONS) {

		//==================== CLEAR SCREEN ====================
		system("cls");

		//==================== DISPLAY VIEW ====================
		mapDisplay.updateMap(map->getCityList());
		mapDisplay.printMap(&markers);	// Display Map Views
		playerDisplay.printPlayerDisplay(players[activePlayer]);  // Display player view

		cout << "=============================================================" << endl;
		cout << "------------------------Phase 1------------------------------" << endl;
		cout << "=============================================================" << endl << endl;

		//display actions
		int action = 0;
		cout << "You have " << (NUM_OF_ACTIONS - i) << " actions left. \nWhich would you like to perform?\n" << endl;
		cout << "Drive OR Ferry (Enter 1)" << endl;
		cout << "Direct Flight (Enter 2)" << endl;
		cout << "Charter Flight (Enter 3)" << endl;
		cout << "Shuttle Flight (Enter 4)" << endl;
		cout << "Build a Research Station (Enter 5)" << endl;
		cout << "Discover A Cure (Enter 6)" << endl;
		cout << "Treat A Disease (Enter 7)" << endl;
		cout << "Share Knowledge (Enter 8)" << endl;
		cout << "Show Reference Card (Enter 9) [NOTE: This does not count as an action!]" << endl;
		cout << "Stop (Enter 10)" << endl;
		
		//process input of actions
		if (!(cin >> action))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			action = 0;
		}
		cout << endl;
		cout << "=======================================================" << endl;

		switch (action)
		{
		case 1:
			if(driveFerry())
				i++;
			break;
		case 2:
			if(directFlight())
				i++;
			break;
		case 3:
			if(charterFlight())
				i++;
			break;
		case 4: 
			if(shuttleFlight());
				i++;
			break;
		case 5:
			if(buildResearchStation())
				i++;
			break;
		case 6:
			if (discoverCure())
				i++;
			break;
		case 7:
			if (treatDisease())
				i++;
			break;
		case 8:
			if(shareKnowledge())
				i++;
			break;
		case 9:
			printRefCard();
			break;
		// Skip turn
		case 10:
			cout << "Ending Actions Turn" << endl;
			i = 4;
			break;
		// Error if action is invalid
		default:
			cout << "Something went wrong, no valid action selected." << endl;
			break;
		}
		pause();
	}
}

// ============================== Drive/Ferry Function =========================================
bool GameController::driveFerry()
{
	cout << "Drive / Ferry Selected: Where would you like to go? " << endl;
	int newLocation = -1;
	vector<CityNode*> connections = players[activePlayer]->getPawn()->getConnections();

	// Check for possible nearby cities 
	for (int i = 0; i < connections.size(); i++) {
		cout << connections[i]->getName() << " (" << i << ")" << endl;
	}
	//Check input
	if (!(cin >> newLocation) || newLocation < 0 || newLocation >= connections.size())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input" << endl;
		return false;
	}
	
	// Change location of the player
	players[activePlayer]->setPawn(connections[newLocation]);
	cout << "Player is now in " << players[activePlayer]->getPawn()->getName() << endl << endl;
	return true;
}

// ============================== Direct Flight Function =========================================
bool GameController::directFlight()
{
	cout << "Direct Flight Selected: Where would you like to go? (To go back to menu enter non-displayed character)" << endl;
	int newLocation = -1;
	vector<CityNode*> connections;
	//go through hand and find city cards and add them to possible connections
	for (int l = 0; l < players[activePlayer]->getNumOfCards(); l++)
	{
		if (players[activePlayer]->getCard(l)->getType() == "City")
		{
			CityCard *card = dynamic_cast<CityCard*>(players[activePlayer]->getCard(l));
			connections.push_back(this->map->getCity(card->getCity()));
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
	if (!(cin >> newLocation) || newLocation < 0 || newLocation >= connections.size())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');		
		cout << "Invalid input" << endl;
		return false;
	}
	
	players[activePlayer]->setPawn(connections[newLocation]);
	//go through hand to find city card used and remove it
	for (int j = 0; j < players[activePlayer]->getNumOfCards(); j++)
	{
		if (players[activePlayer]->getCard(j)->getType() == "City")
		{
			CityCard *card = (dynamic_cast<CityCard*>(players[activePlayer]->getCard(j)));
			if (card->getCity() == players[activePlayer]->getPawn()->getName())
			{
				players[activePlayer]->removeCard(j);
				delete card;
				card = nullptr;
			}
		}
	}

	cout << "Player is now in " << players[activePlayer]->getPawn()->getName() << endl << endl;
	return true;
}

// ============================== Charter Flight Function =========================================
bool GameController::charterFlight()
{
	cout << "Charter Flight Selected: Where would you like to go?" << endl;
	bool charterFlightPossible = false;
	int newLocation = -1;

	// Checks hand for City Card
	for (int j = 0; j < players[activePlayer]->getNumOfCards(); j++)
	{
		if (players[activePlayer]->getCard(j)->getType() == "City")
		{
			CityCard *card = (dynamic_cast<CityCard*>(players[activePlayer]->getCard(j)));
			if (card->getCity() == players[activePlayer]->getPawn()->getName())
			{
				charterFlightPossible = true;
			}
		}
	}

	// If flight is possible
	if (charterFlightPossible)
	{
		for (int k = 0; k < NUM_OF_CITIES; k++)
		{
			string name = this->map->getCityList()->at(k)->getName();
			cout << name << " (" << k << ")\t";
			if (k % 12 == 11)
			{
				cout << endl;
			}
		}
		//Check input
		if (!(cin >> newLocation) || newLocation < 0 || newLocation >= NUM_OF_CITIES)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input" << endl;
			return false;
		}

		// Search for the card and remove it 
		for (int l = 0; l < players[activePlayer]->getNumOfCards(); l++)
		{
			if (players[activePlayer]->getCard(l)->getType() == "City")
			{
				CityCard *card = (dynamic_cast<CityCard*>(players[activePlayer]->getCard(l)));
				if (card->getCity() == players[activePlayer]->getPawn()->getName())
				{
					players[activePlayer]->removeCard(l);
					delete card;
					card = nullptr;
				}
			}
		}

		// Change the location of the player
		players[activePlayer]->setPawn(this->map->getCityList()->at(newLocation));
		cout << "Player is now in " << players[activePlayer]->getPawn()->getName() << endl << endl;
		return true;
	}

	// Error if Charter Flight is impossible 
	else
	{
		cout << "Sorry, Charter Flight is not possible right now." << endl;
		return false;
	}
}

// ============================== Shuttle Flight Function =========================================
bool GameController::shuttleFlight()
{
	// Check whether player is at a research station
	if (!players[activePlayer]->getPawn()->hasResearchStation()) {
		cout << "You are currently not on a research station! " << endl;
		return false;
	}

	else {
		cout << "Shuttle Flight Selected: Where would you like to go? " << endl;
		vector<CityNode*>* cityList = map->getCityList();
		vector<CityNode*> researchStation;

		// Goes through every city and check if it has a research station
		for (int i = 0; i < cityList->size(); i++) {
			if (cityList->at(i)->hasResearchStation()) {
				researchStation.push_back(cityList->at(i));
			}
		}

		// Print out list of cities with research station
		for (int i = 0; i < researchStation.size(); i++) {
			cout << researchStation[i]->getName() << " (" << i << ")" << endl;
		}

		int newLocation = -1;
		//Check input
		if (!(cin >> newLocation) || newLocation < 0 || newLocation >= researchStation.size())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input" << endl;
			return false;
		}

		// Move Player to the City 
		if (newLocation < 0 || newLocation > researchStation.size()) {
			cout << "Invalid Selection!";
			return false;
		}
		else if (players[activePlayer]->getPawn()->getName() == researchStation.at(newLocation)->getName()) {

			cout << "You are already in this city!";
			return false;
		}
		else {
			players[activePlayer]->setPawn(researchStation[newLocation]);
			cout << "Player is now in " << players[activePlayer]->getPawn()->getName() << endl << endl;
			return true;
		}
	}
}

// ============================== Build Research Station Function =========================================
bool GameController::buildResearchStation()
{
	cout << "Build a Research Station Selected" << endl;
	//Check if player has the card for the city they are in
	bool researchStationPossible = false;
	int index;
	for (index = 0; index < players[activePlayer]->getNumOfCards(); index++)
	{
		if (players[activePlayer]->getCard(index)->getType() == "City")
		{
			if (dynamic_cast<CityCard*>(players[activePlayer]->getCard(index))->getCity() == players[activePlayer]->getPawn()->getName())
			{
				researchStationPossible = true;
				break;
			}
		}
	}
	//Try to build research station
	if (researchStationPossible) {
		//Build a research station
		if (markers.useResearchStation()) {
			players[activePlayer]->getPawn()->addResearchStation();
			cout << "Research Station Added! ";
			Card* card = players[activePlayer]->removeCard(index);
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

// ==============================  Discover Cure Function =========================================
bool GameController::discoverCure()
{ 
	//Check if player is at a city with a research station.
	if (players[activePlayer]->getPawn()->hasResearchStation()) {
		cout << "Please select 5 cards of the same color." << endl;
		displayPlayerCardOptions(activePlayer);

		int count[NUM_OF_DISEASES] = { 0 };
		int answer[NUM_OF_CARDS_TO_CURE] = { 0 };
		//Player selects 5 cards for cure
		for (int i = 0; i < NUM_OF_CARDS_TO_CURE; i++) {
			//Checks for valid input
			if (!(cin >> answer[i]) || answer[i] < 0 || answer[i] >= players[activePlayer]->getNumOfCards())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input." << endl;
				return false;
			}
			count[dynamic_cast<CityCard*>(players[activePlayer]->getCard(answer[i]))->getColor()]++;
		}
		//Check if requirements have been met and cure if so.
		for (int i = 0; i < NUM_OF_DISEASES; i++) {
			if (count[i] == NUM_OF_CARDS_TO_CURE) {
				cout << "Now curing the " << infectTypeEnumToString(static_cast<InfectType>(i)) << " disease." << endl;
				markers.cureDiseaseUpdateMarker(static_cast<InfectType>(i));
				Card* card;
				for (int j = 0; j < NUM_OF_CARDS_TO_CURE; j++) {
					card = players[activePlayer]->removeCard(answer[j]);
					delete card;
					card = nullptr;
				}
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

// ==============================  Treat Disease Function =========================================
bool GameController::treatDisease()
{
	//Player chooses which disease to treat
	cout << "What color disease would you like to treat?" << endl;
	for (int i = 0; i < NUM_OF_DISEASES; i++) {
		cout << i << ") " << infectTypeEnumToString(static_cast<InfectType>(i)) << endl;
	}
	int answer;

	//Checks for valid input
	if (!(cin >> answer) || answer < 0 || answer >= NUM_OF_DISEASES)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input" << endl;
		return false;
	}

	InfectType infection = static_cast<InfectType>(answer);
	CityNode* city = players[activePlayer]->getPawn();

	//If Disease is cured - remove all cubes of color
	if (markers.getCureMarker(infection) == cured) {
		int cubesToRemove = city->getInfectionLevel(infection);
		for (int i = 0; i < cubesToRemove; i++) {
			city->reduceInfectionLevel(infection);
			markers.addDiseaseCube(infection);
		}
		cout << "All blocks of disease " << infectTypeEnumToString(infection) << " have been removed. You know the cure!" << endl;
		checkifDiseaseEradicated(infection);
		return true;
	}
	//If Disease is not cured - remove one cube of color
	else if (city->getInfectionLevel(infection) > 0){
		city->reduceInfectionLevel(infection);
		markers.addDiseaseCube(infection);
		cout << "One block of disease " << infectTypeEnumToString(infection) << " has been removed." << endl;
		checkifDiseaseEradicated(infection);
		return true;
	}
	//No cubes in city to remove
	else {
		cout << "No infection of color " << infectTypeEnumToString(infection) << " here to cure." << endl;
		return false;
	}
}

// ============================== Share Knowledge Function =========================================
//Player can give other player a card if in the same city, and the card matches the city
bool GameController::shareKnowledge()
{
	int cardToPass = -1;
	int playerWithCard = -1;
	int otherPlayer = -1;
	cout << "Share Knowledge Selected." << endl;

	//Ask who they would like to share knowledge with
	cout << "Which player would you like to share knowlege with?" << endl;
	for (int i = 0; i < NUM_OF_PLAYERS; i++) {
		if (i != activePlayer) {
			cout << "- Player " << i+1 << endl;
		}
	}
	//Checks for valid input
	if (!(cin >> otherPlayer))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input" << endl;
		return false;
	}
	otherPlayer -= 1;

	// Checks if players are in the same city
	//int otherPlayer = (activePlayer + 1) % NUM_OF_PLAYERS;
	if (players[activePlayer]->getPawn() != players[otherPlayer]->getPawn()) {
		cout << "Sorry, you and the other player are not in the same city, you cannot share a card." << endl;
		return false;
	}

	// Searches active players hand for City cards that match location
	for (int j = 0; j < players[activePlayer]->getNumOfCards(); j++)
	{
		if (players[activePlayer]->getCard(j)->getType() == "City")
		{
			CityCard *card = (dynamic_cast<CityCard*>(players[activePlayer]->getCard(j)));
			if (card->getCity() == players[activePlayer]->getPawn()->getName()) {
				cardToPass = j;
				playerWithCard = activePlayer;
				cout << "You have the card for this city, you may pass it." << endl;
				break;
			}
		}
	}

	// Searches other player's hand for City cards that match location
	for (int j = 0; j < players[otherPlayer]->getNumOfCards(); j++)
	{
		if (players[otherPlayer]->getCard(j)->getType() == "City")
		{
			CityCard *card = (dynamic_cast<CityCard*>(players[otherPlayer]->getCard(j)));
			if (card->getCity() == players[activePlayer]->getPawn()->getName()) {
				cardToPass = j;
				playerWithCard = otherPlayer;
				cout << "The other player has the card for this city, they may pass it." << endl;
				break;
			}
		}
	}

	//Check if no card found
	if (cardToPass == -1) {
		cout << "Neither of you have the card for " << players[activePlayer]->getPawn()->getName() << " and so cannot share." << endl;
		return false;
	}

	// Get other player's approval
	cout << "\nPlayer " << otherPlayer + 1 << " , do you approve this trade? (y/n)" << endl;
	char answer;
	//Checks for valid input
	if (!(cin >> answer))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input" << endl;
		return false;
	}

	//If approved Transfer card
	if (answer == 'y' || answer == 'Y'){
		int playerWithoutCard = (playerWithCard + 1) % NUM_OF_PLAYERS;

		Card* card = players[playerWithCard]->removeCard(cardToPass);
		players[playerWithoutCard]->addCard(card);
		checkPlayerHandSize(playerWithoutCard);
		cout << "You have successfully passed the " << players[activePlayer]->getPawn()->getName() << " card." << endl;
		return true;
	}
	else {
		cout << "The other player has rejected your request" << endl;
		return false;
	}
}

// Print out reference card
void GameController::printRefCard() {
	system("cls");
	ReferenceCard refCard;
	cout << refCard.print() << endl;
}

void GameController::checkifDiseaseEradicated(InfectType infection)
{
	if (markers.getCureMarker(infection) == cured) {
		if (markers.getNumOfDiseaseCubes(infection) == NUM_OF_DISEASE_CUBES_PER_TYPE) {
			markers.eradicateDiseaseUpdateMarker(infection);
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
// -----PHASE 2--------
/////////////////////////////////////////////////////////////////////////////////////////////////////

void GameController::phase2_DrawCards()
{
	system("cls");
	cout << "=============================================================" << endl;
	cout << "------------------------Phase 2------------------------------" << endl;
	cout << "=============================================================" << endl << endl;
	cout << "Player " << activePlayer + 1 << " draws two cards" << endl;
	
	//Check how many cards left in draw pile
	if (playerDeck->cardsInDeck() < 2);
		// GAME OVER

	//Draw two cards
	for (int i = 0; i < NUM_OF_PLAYER_CARDS_DRAWN_PER_TURN; i++) {
		drawPlayerCard();
	}

	pause();
}

//Draws a card and adds it to player hand or calls epidemic card handler
void GameController::drawPlayerCard()
{
	//Draw a card
	Card* card = playerDeck->drawFromTop();
	cout << "\nPlayer " << activePlayer+1 << " has drawn a " << card->getType() << " card" << endl;
	
	//Check if epidemic card
	if (card->getType() == "Epidemic") {
		epidemicCardActions();
		delete card;
	}
	//If a city or event card -> Add to hand
	else {
		cout << "The card has been added to player " << activePlayer + 1 << "'s hand" << endl;
		cout << "\t- " << card->print() << endl;
		players[activePlayer]->addCard(card);

		//Check if players' hand of cards is too large
		checkPlayerHandSize(activePlayer);
	}
}

//called when player draws an epidemic card
void GameController::epidemicCardActions()
{
	cout << "\n---------An Epidemic Card has been Pulled!!!-----------" << endl << endl;
	//Increase infection Rate
	markers.increaseInfectRate();
	cout << "Infection Rate has increased to " << markers.getInfectionRate() << endl;
	
	//Add 3 cubes to a city or until an outbreak occurs
	InfectionCard* card = dynamic_cast<InfectionCard*>(infectionDeck->drawFromBottom());
	cout << "Infection Card drawn - " << card->print() << endl;
	CityNode* city = map->getCity(card->getCity());
	InfectType infection = card->getColor();
	infectionDeck->discard(card);
	int outbreakCounterBefore = markers.getOutbreakCounter();

	for (int i = 0; i < EPIDEMIC_INFECTION || markers.getOutbreakCounter() != outbreakCounterBefore; i++) {
		infectCity(city, infection);
	}
	outbreakHistory.clear();

	//Reshuffle discard pile and add to top of draw pile
	infectionDeck->discardToDraw();
	cout << "The infection deck discard pile has been shuffled and added to the top of the draw pile." << endl;
}

//Called when Player has too many cards in hand
void GameController::discardPlayerCard(int playerIndex)
{
	cout << "\nPlayer " << playerIndex + 1 << " has too many cards in hand! Select one to discard:" << endl;
	displayPlayerCardOptions(playerIndex);
	int answer;

	// Check input
	if (!(cin >> answer) || answer < 0 || answer >= players[playerIndex]->getNumOfCards())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input" << endl;
		system(0);
	}

	// Discard Card
	Card* card = players[playerIndex]->removeCard(answer);
	delete card;
	card = nullptr;
	cout << "Discarding Card\n" << endl;
}

//Check if players' hand of cards is too large
void GameController::checkPlayerHandSize(int playerIndex)
{
	if (players[playerIndex]->getNumOfCards() > MAX_HAND_SIZE) {
		discardPlayerCard(playerIndex);
	}
}

//Prints cards in hand, in order to select from them.
void GameController::displayPlayerCardOptions(int playerIndex)
{
	for (int i = 0; i < players[playerIndex]->getNumOfCards(); i++) {
		Card* card = players[playerIndex]->getCard(i);
		cout << i << ") " << card->print() << endl;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
// -----PHASE 3--------
/////////////////////////////////////////////////////////////////////////////////////////////////////

//  Phase 3: End Turn Infection 
void GameController::phase3_Infects()
{
	system("cls");
	cout << "=============================================================" << endl;
	cout << "------------------------Phase 3------------------------------" << endl;
	cout << "=============================================================" << endl << endl;
	cout << "Player " << activePlayer + 1 << " draws " << markers.getInfectionRate() << " infection cards." << endl << endl;
	
	//Draw Cards and infect cities
	for (int i = 0; i < markers.getInfectionRate(); i++) {
		InfectionCard* card = dynamic_cast<InfectionCard*>(infectionDeck->drawFromTop());
		if (markers.getCureMarker(card->getColor()) != eradicated) {
			cout << "- " << card->print() << endl;
			infectCity(map->getCity(card->getCity()), card->getColor());
			cout << endl;
		}
		infectionDeck->discard(static_cast<Card*>(card));
	}
	outbreakHistory.clear();
	pause();
}

//Adds a disease cube to a city
void GameController::infectCity(CityNode* city, InfectType infection)
{
	//Infect city, add cube of infection color to city
	if (city->getInfectionLevel(infection) < MAX_CUBES_PER_CITY) {
		cout << "A " << infectTypeEnumToString(infection) << " cube has been added to " << city->getName() << endl;
		city->increaseInfectionLevel(infection);
		bool remainder = markers.useDiseaseCube(infection);
		//check if all cubes of a color have been used.
		if (!remainder) {
			//game over
		}
	}
	//Outbreak occurs, city already had three disease cubes of infection color
	//All connecting cities will be infected.
	else {
		//track cities that have had an outbreak this chain.
		outbreakHistory.push_back(city->getName());
		handleOutbreak(city, infection);
	}
}

//Handles Outbreak events
void GameController::handleOutbreak(CityNode * city, InfectType infection)
{
	//increase counter and check if it has reached maximum
	markers.increaseOutbreakCounter();
	if (markers.getOutbreakCounter() == MAX_OUTBREAKES) {
		//game over
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
			infectCity(connections[i], infection);
		}
	}
}

