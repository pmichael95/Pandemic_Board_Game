#pragma once

#include "CommonLibrary.h"
#include "Map.h"
#include "Markers.h"
#include "Cards.h"
#include "Player.h"
#include "MapView.h"
#include "PlayerView.h"

class GameController
{
	int activePlayer;

	//Game Models
	Markers markers;
	GameMap* map;
	Deck* infectionDeck;
	Deck* playerDeck;
	Player* players[NUM_OF_PLAYERS];

	//Keeps track of chains of outbreaks to eliminate repeats
	vector<string> outbreakHistory;

	//Views
	MapView mapDisplay;
	PlayerView playerDisplay;

public:
	// Constructor
	GameController();

	// Destructor
	~GameController();


	void initializeNewGame();
	void loadGame();
	void saveGame();

	void startRound();

private:
	//INITIALIZE HELPER FUNCTIONS///////////////////////////////////
	void initializePlayers();
	void initialInfection();
	void addEpidemicCards();

	void switchPlayers();
	void pause();

	//PHASE 1 ACTIONS//////////////////////////////////////////////
	void phase1_Actions();
	
	bool driveFerry();
	bool directFlight();
	bool charterFlight();
	bool shuttleFlight();
	bool buildResearchStation();
	bool discoverCure();
	bool treatDisease();
	bool shareKnowledge();
	void printRefCard();

	void checkifDiseaseEradicated(InfectType infection);

	//PHASE 2 DRAW CARDS////////////////////////////////////////////
	void phase2_DrawCards();

	void drawPlayerCard();
	void epidemicCardActions();
	void discardPlayerCard(int playerIndex);
	void checkPlayerHandSize(int playerIndex);
	void displayPlayerCardOptions(int playerIndex);

	//PHASE 3 INFECTION ////////////////////////////////////////////
	void phase3_Infects();

	void infectCity(CityNode* city, InfectType infection);
	void handleOutbreak(CityNode* city, InfectType infection);
};

