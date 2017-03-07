#pragma once

#include "CommonLibrary.h"
#include "Map.h"
#include "Cards.h"

//PLAYER CLASS/////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Player
{
	//Attributes/////////////////////////////////
	int id;
	CityNode* pawn;
	vector<Card*> cardsInHand;
	ReferenceCard* reference; // or string* referenceCard ??
	RoleCard* role;

public:
	//Constructors////////////////////////////////
	Player();
	Player(int id, ReferenceCard* referenceCard);
	~Player();

	//Get and Set/////////////////////////////////
	void setPawn(CityNode* position);
	CityNode* getPawn();

	RoleCard* getRole();
	void setRole(RoleCard* role);
	ReferenceCard* getReferenceCard();

	//Card Methods///////////////////////////////
	int getNumOfCards();
	Card* getCard(int index);
	void addCard(Card*);
	Card* removeCard(int index);
};

