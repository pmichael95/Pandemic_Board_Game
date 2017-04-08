#pragma once

#include "CommonLibrary.h"
#include "InputOutput.h"
#include "Map.h"
#include "Player.h"
#include "Markers.h"

class Strategy
{
public:
	Strategy() {}
	~Strategy() {}

	virtual bool execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer) = 0;

//common helper functions
protected:
	//Selects which players pawn will be moved. Handles special Dispatcher case
	void pawnSelection(vector<Player*> playerList, int activePlayer, int &movingPawn);

	//Called to get rid of a card when Player has too many cards in hand
	void Strategy::discardPlayerCard(Player* player, Deck* playerDeck);

	//Places a disease cube in a city
	void infectCity(CityNode* city, InfectType infection, vector<string> outbreakHistory, Markers* markers, vector<Player*> playerList);

	//Checks if city is next to a Quarentine Specialist or a Medic
	//Returns true, if city affected by Quarentine Specialist
	bool quarentineCheck(CityNode* city, vector<Player*> playerList, bool isCured);

	//Handles infection of connected cities in the case of an outbreak
	void handleOutbreak(CityNode * city, InfectType infection, vector<string> outbreakHistory, Markers* markers, vector<Player*> playerList);
};

