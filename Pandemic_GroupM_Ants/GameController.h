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

	//Do these need to be passed to the views?
	Markers markers;
	GameMap* map;
	Deck* infectionDeck;
	Deck* playerDeck;
	Player* players[NUM_OF_PLAYERS];

	//Views
	MapView    mapDisplay;
	PlayerView playerDisplay;

public:
	GameController();
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

	//PHASE 2 DRAW CARDS////////////////////////////////////////////
	void phase2_DrawCards();
	void drawPlayerCard();
	void epidemicCardActions();
	void discardPlayerCard();

	//PHASE 3 INFECTION ////////////////////////////////////////////
	void phase3_Infects();
	void infectCity(CityNode* city, InfectType infection);
};

