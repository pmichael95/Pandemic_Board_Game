#pragma once

#include "Strategy.h"
#include "InputOutput.h"

///////////////////////////////////////////////////////////////////////////////////////////////
// PHASE I ACTION CLASSES
//////////////////////////////////////////////////////////////////////////////////////////////

class DriveFerry : public Strategy
{
public:
	DriveFerry() {}
	~DriveFerry() {}

	//Player can move to a connecting city
	bool execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer);
};

class DirectFlight : public Strategy
{
public:
	DirectFlight() {}
	~DirectFlight() {}

	//Player can discard a city card to fly directly to that city
	bool execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer);
};

class CharterFlight : public Strategy
{
public:
	CharterFlight() {}
	~CharterFlight() {}

	//Player can discard a card matching their current city and move anywhere
	bool execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer);
};

class ShuttleFlight : public Strategy
{
public:
	ShuttleFlight() {}
	~ShuttleFlight() {}

	//A Player in a city with a Research Station can move to any other city with a Research Station
	bool execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer);
};

class DispatcherMovement : public Strategy
{
public:
	DispatcherMovement() {}
	~DispatcherMovement() {}

	//Dispatcher ONLY, can move any players pawn to the location of another players pawn.
	bool execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer);
};

class BuildResearchStation : public Strategy
{
public:
	BuildResearchStation() {}
	~BuildResearchStation() {}

	//Player can build a research station in their current city if they discard the matching city card.
	bool execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer);
};

class DiscoverCure : public Strategy
{
public:
	DiscoverCure() {}
	~DiscoverCure() {}

	//By Discarding 5 cards of the same color, the player can cure the disease of that color
	bool execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer);
};

class TreatDisease : public Strategy
{
public:
	TreatDisease() {}
	~TreatDisease() {}

	//Player removes cubes of a disease from a city
	bool execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer);
private:
	void checkifDiseaseNowEradicated(Markers* markers, InfectType infection);
};

class ShareKnowledge : public Strategy
{
public:
	ShareKnowledge() {}
	~ShareKnowledge() {}

	//Player can give other player a card if in the same city, and the card matches the city
	bool execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer);

private:
	//Transfers the card from one players hand to another and checks player hand size
	void transferCard(int cardToPass, Player* fromPlayer, Player* toPlayer, Deck* playerDeck);
};

class ShowRefCard : public Strategy
{
public:
	ShowRefCard() {}
	~ShowRefCard() {}

	//Player views Reference Card description
	bool execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer);

};

class TakeEventCard : public Strategy
{
public:
	TakeEventCard() {}
	~TakeEventCard() {}

	//Player views Reference Card description
	bool execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer);

};

class DoNothing : public Strategy
{
public:
	DoNothing() {}
	~DoNothing() {}

	//Keeps program from crashing when player chooses not to act
	bool execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer);

};

///////////////////////////////////////////////////////////////////////////////////////////////
// PHASE II ACTION CLASSES
//////////////////////////////////////////////////////////////////////////////////////////////

class DrawCard : public Strategy
{
public:
	DrawCard() {}
	~DrawCard() {}

	//Player draws a card and adds to hand or takes Epidemic card options
	bool execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer);
private:
	//Handles events that occur when an Epidemic card is pulled
	void epidemicCardActions(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* infectionDeck);
};

///////////////////////////////////////////////////////////////////////////////////////////////
// PHASE III ACTION CLASSES
//////////////////////////////////////////////////////////////////////////////////////////////

class Infect : public Strategy
{
public:
	Infect() {}
	~Infect() {}

	//Keeps program from crashing when player chooses not to act
	bool execute(GameMap* map, Markers* markers, vector<Player*> playerList, Deck* playerDeck, Deck* infectionDeck, int activePlayer);

};