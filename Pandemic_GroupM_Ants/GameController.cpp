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
		Card* card = new EpidemicCard();
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

void GameController::pause()
{
	cout << "\nReady to continue? (Enter any key)" << endl;
	cin.get();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
// -----PHASE 1--------
/////////////////////////////////////////////////////////////////////////////////////////////////////

void GameController::phase1_Actions()
{
	cout << endl << "Phase I" << endl;
	for (int i = 0; i < NUM_OF_ACTIONS; i++) {


		//==================== DISPLAY VIEW ====================
		mapDisplay.updateMap(map->getCityList());
		mapDisplay.printMap();	// Display Map View

		playerDisplay.printPlayerDisplay(players[activePlayer]);  // Display player view


		//display actions
		int action = 0;
		cout << "You have " << (NUM_OF_ACTIONS - i) << " actions left, What would you like to do?" << endl;
		cout << "Drive / Ferry (1)" << endl;
		cout << "Direct Flight (2)" << endl;
		cout << "Charter Flight (3)" << endl;
		cout << "Shuttle Flight (4)" << endl;
		cout << "Build A Research Station (5)" << endl;
		cout << "Discover A Cure (6)" << endl;
		cout << "Treat A Disease (7)" << endl;
		cout << "Share Knowledge (8)" << endl;
		cout << "Stop (9)" << endl;
		
		//process input of actions
		cin >> action;

		switch (action)
		{
		case 1:	//Drive / Ferry
		{
			cout << "Drive / Ferry Selected" << endl;
			int newLocation = 0;
			vector<CityNode*> connections = players[activePlayer]->getPawn()->getConnections();
			for (int i = 0; i < connections.size(); i++) {
				cout << connections[i]->getName() << " (" << i << ")" << endl;
			}
			cin >> newLocation;
			players[activePlayer]->setPawn(connections[newLocation]);
			cout << "Player is now in " << players[activePlayer]->getPawn()->getName() << endl << endl;
			break;
		}
		case 2:	//Direct Flight
		{
			cout << "Direct Flight Selected" << endl;
			int newLocation = 0;
			vector<CityNode*> connections;
			//go through hand and find city cards and add them to possible connections
			for (int i = 0; i < players[activePlayer]->getNumOfCards(); i++)
			{
				if (players[activePlayer]->getCard(i)->getType() == "City")
				{
					CityCard *card = (dynamic_cast<CityCard*>(players[activePlayer]->getCard(i)));
					connections.push_back(this->map->getCity(card->getCity()));
				}
			}
			//print out where the player can fly
			for (int i = 0; i < connections.size(); i++) {
				cout << connections[i]->getName() << " (" << i << ")" << endl;
			}
			//set player to new location
			cin >> newLocation;
			players[activePlayer]->setPawn(connections[newLocation]);
			//go through hand to find city card used and remove it
			for (int i = 0; i < players[activePlayer]->getNumOfCards(); i++)
			{
				if (players[activePlayer]->getCard(i)->getType() == "city")
				{
					CityCard *card = (dynamic_cast<CityCard*>(players[activePlayer]->getCard(i)));
					if (card->getCity() == players[activePlayer]->getPawn()->getName())
					{
						players[activePlayer]->removeCard(i);
					}
				}
			}

			cout << "Player is now in " << players[activePlayer]->getPawn()->getName() << endl << endl;
			
			break;
		}
		case 3:
			cout << "Charter Flight Selected" << endl;
			break;
		case 4:
			cout << "Shuttle Flight Selected" << endl;
			break;
		case 5:
			cout << "Build A Research Station Selected" << endl;
			break;
		case 6:
			cout << "Discover A Cure Selected" << endl;
			break;
		case 7:
			cout << "Treat Disease Selected" << endl;
			break;
		case 8:
			cout << "Share Knowledge Selected" << endl;
			break;
		case 9:
			cout << "Ending Actions Turn" << endl;
			i = 4;
			break;
		default:
			cout << "Something went wrong, no action selected" << endl;
			break;
		}

		// Clear Screen after Display to redraw after turn
		mapDisplay.clearScreen();
		playerDisplay.clearPlayerDisplay();
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
// -----PHASE 2--------
/////////////////////////////////////////////////////////////////////////////////////////////////////

void GameController::phase2_DrawCards()
{
	system("cls");
	//announce phase 2
	cout << "Phase 2" << endl;
	cout << "Player "<< activePlayer+1 <<" draws two cards" << endl;
	if (playerDeck->cardsInDeck() < 2);
		// GAME OVER
	for (int i = 0; i < NUM_OF_PLAYER_CARDS_DRAWN_PER_TURN; i++) {
		drawPlayerCard();
	}
	pause();
}

void GameController::drawPlayerCard()
{
	Card* card = playerDeck->drawFromTop();
	cout << "Player " << activePlayer+1 << " has drawn a " << card->getType() << " card" << endl;
	if (card->getType() == "epidemic") {
		epidemicCardActions();
		delete card;
	}
	else {
		cout << "Card is added to player " << activePlayer + 1 << " hand" << endl;
		players[activePlayer]->addCard(card);
		if (players[activePlayer]->getNumOfCards() > MAX_HAND_SIZE) {
			discardPlayerCard();
		}
	}
}

//called when player draws an epidemic card
void GameController::epidemicCardActions()
{
	//Increase infection Rate
	markers.increaseInfectRate();
	cout << "Infection Rate has increased to " << markers.getInfectionRate() << endl;
	
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
	cout << "The infection deck discard pile has been shuffled and added to the top of the draw pile." << endl;
}

//Called when Player has too many cards in hand
void GameController::discardPlayerCard()
{
	cout << "\nPlayer " << activePlayer + 1 << " has too many cards in your hand, select one to discard" << endl;
	for (int i = 0; i < players[activePlayer]->getNumOfCards(); i++) {
		Card* card = players[activePlayer]->getCard(i);
		string name;
		string cardInfo;
		if (card->getType() == "city") {
			name = dynamic_cast<CityCard*>(card)->getCity();
			cout << i << ") ";
			dynamic_cast<CityCard*>(card)->print();
		}
		else if (card->getType() == "event"){
			name = dynamic_cast<EventCard*>(card)->getName();
			cout << i << ") ";
			dynamic_cast<EventCard*>(card)->print();
		}
		//cout << "[" << card->getType() << "] " << name << " (" <<i << ")" << endl;
	}
	int answer;
	cin >> answer;
	players[activePlayer]->removeCard(answer);
	cout << "Discarding Card\n" << endl;
	
}



/////////////////////////////////////////////////////////////////////////////////////////////////////
// -----PHASE 3--------
/////////////////////////////////////////////////////////////////////////////////////////////////////

void GameController::phase3_Infects()
{
	system("cls");
	//announce phase 3
	cout << "Phase 3" << endl;
	cout << "Player " << activePlayer + 1 << " draws " << markers.getInfectionRate() << " infection cards." << endl;
	for (int i = 0; i < markers.getInfectionRate(); i++) {
		InfectionCard* card = dynamic_cast<InfectionCard*>(infectionDeck->drawFromTop());
		//show card???
		if (markers.getCureMarker(card->getColor()) != eradicated) {
			infectCity(map->getCity(card->getCity()), card->getColor());
		}
		infectionDeck->discard(static_cast<Card*>(card));
	}
	pause();
}

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
		markers.increaseOutbreakCounter();
		cout << "An outbreak has occurred" << endl;
		vector<CityNode*> connections = city->getConnections();
		for (int i = 0; i < connections.size(); i++) {
			infectCity(connections[i], infection);
		}
		if (markers.getOutbreakCounter() == MAX_OUTBREAKES) {
			//game over
		}
	}
}