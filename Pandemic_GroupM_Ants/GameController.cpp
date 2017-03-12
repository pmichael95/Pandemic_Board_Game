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

void GameController::initializeNewGame()
{
	//initialize models
	map = new GameMap(MAP_INITIAL_FILE);
	infectionDeck = new Deck(INFECTION_CARD_INITIAL_FILE);
	playerDeck = new Deck(PLAYER_CARD_INITIAL_FILE);

	//Setup starting conditions
	map->getHead()->addResearchStation();
	initializePlayers();
	addEpidemicCards();
	initialInfection();
}

void GameController::initializePlayers() 
{
	ReferenceCard* ref = new ReferenceCard();
	Deck* roleDeck = new Deck(ROLE_CARD_INITIAL_FILE);
	for (int i = 0; i < NUM_OF_PLAYERS; i++) {
		players[i] = new Player(i, ref);
		players[i]->setPawn(map->getHead());
		players[i]->setRole(dynamic_cast<RoleCard*>(roleDeck->drawFromTop()));
		for (int j = 0; j < NUM_OF_STARTING_CARDS_PER_PLAYER; j++) {
			players[i]->addCard(playerDeck->drawFromTop());
		}
	}
	delete roleDeck;
}

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
		Card* card = new EpidemicCard(); //do we really need a parameratized constructor, all the same.
		playerDeck->addCard(card);
	}
	playerDeck->shuffleDeck();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// -----SAVE/LOAD--------
/////////////////////////////////////////////////////////////////////////////////////////////////////

void GameController::loadGame()
{ //Serialization
}

void GameController::saveGame()
{ //Serialization
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// -----GAME ROUND--------
/////////////////////////////////////////////////////////////////////////////////////////////////////

void GameController::startRound()
{
	for (int i = 0; i < NUM_OF_PLAYERS; i++) {
		phase1_Actions();
		phase2_DrawCards();
		phase3_Infects();
		switchPlayers();
	}
}

void GameController::switchPlayers()
{	activePlayer = (activePlayer + 1) % NUM_OF_PLAYERS;	}


/////////////////////////////////////////////////////////////////////////////////////////////////////
// -----PHASE 1--------
/////////////////////////////////////////////////////////////////////////////////////////////////////

void GameController::phase1_Actions()
{
	for (int i = 0; i < NUM_OF_ACTIONS; i++){
		//display view
		//display actions
		//process input of actions
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
// -----PHASE 2--------
/////////////////////////////////////////////////////////////////////////////////////////////////////

void GameController::phase2_DrawCards()
{
	//announce phase 2
	//If(check number of cards in draw pile ---NEED FUNCTION!--- is < 2)
		//-> GAME OVER
	for (int i = 0; i < NUM_OF_PLAYER_CARDS_DRAWN_PER_TURN; i++) {
		drawPlayerCard();
	}
}

void GameController::drawPlayerCard()
{
	Card* card = playerDeck->drawFromTop();
	//show card drawn???
	if (card->getType() == "Epidemic") { //types for cards (call super constructor) not done, needs to be fixed
		epidemicCardActions();
		delete card;
	}
	else {
		players[activePlayer]->addCard(card);
		if (players[activePlayer]->getNumOfCards() > MAX_HAND_SIZE) {
			//player must discard one card //view call?? //function in player?
		}
	}
}

void GameController::epidemicCardActions()
{
	//Increase infection Rate
	markers.increaseInfectRate();
	
	//Add 3 cubes to a city or until an outbreak occurs
	InfectionCard* card = dynamic_cast<InfectionCard*>(infectionDeck->drawFromBottom());
	CityNode* city = map->getCity(card->getCity());
	InfectType infection = card->getColor();
	infectionDeck->discard(card);
	int outbreakMemory = markers.getOutbreakCounter();

	for (int i = 0; i < EPIDEMIC_INFECTION || markers.getOutbreakCounter() != outbreakMemory; i++) {
		infectCity(city, infection);
	}

	//Reshuffle discard pile and add to top of draw pile
	infectionDeck->discardToDraw();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// -----PHASE 3--------
/////////////////////////////////////////////////////////////////////////////////////////////////////

void GameController::phase3_Infects()
{
	//announce phase 3
	for (int i = 0; i < markers.getInfectionRate(); i++) {
		InfectionCard* card = dynamic_cast<InfectionCard*>(infectionDeck->drawFromTop());
		//show card???
		if (markers.getCureMarker(card->getColor()) != eradicated) {
			infectCity(map->getCity(card->getCity()), card->getColor());
		}
		infectionDeck->discard(static_cast<Card*>(card));
	}
}

void GameController::infectCity(CityNode* city, InfectType infection)
{
	//Infect city, add cube of infection color to city
	if (city->getInfectionLevel(infection) < MAX_CUBES_PER_CITY) {
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
		markers.increaseOutbreakCounter();
		cout << "An outbreak has occurred" << endl;
		vector<CityNode*> connections = city->getConnections();
		for (int i = 0; i < connections.size(); i++) {
			infectCity(connections[i], infection);
		}
	}
}