#pragma once

#include "CommonLibrary.h"
#include "Map.h"
#include "Cards.h"
#include "InputOutput.h"

//PLAYER CLASS/////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Player : public Subject
{
	//Attributes/////////////////////////////////
	int id;
	CityNode* pawn;
	vector<Card*> cardsInHand;
	ReferenceCard* reference;
	RoleCard* role;
	Card* extraPlannerCard;

	//Serialize//////////////////
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive& ar, const unsigned version) {
		ar.template register_type<Card>();
		ar.template register_type<CityNode>();
		ar & id & pawn & cardsInHand & reference & role;
	}

public:
	//Constructors////////////////////////////////
	Player();
	Player(int id, ReferenceCard* referenceCard);
	~Player();

	//Get and Set/////////////////////////////////

	// OBSERVER PATTERN: Setting Pawn Location
	void setPawn(CityNode* position);
	CityNode* getPawn() { return this->pawn; }

	int getId() { return id; }

	RoleCard* getRole() { return this->role; }
	// OBSERVER PATTERN: Setting Player Role
	void setRole(RoleCard* role);

	ReferenceCard* getReferenceCard() { return this->reference; }

	void addExtraPlannerCard(Card* card);
	Card* useExtraPlannerCard();

	//Card Methods///////////////////////////////
	int checkifPlayerHasCard(string name);
	bool checkifPlayerHasCardAtIndex(string name, int index);
	void displayPlayerCardOptions();
	//Called to get rid of a card when Player has too many cards in hand
	void discardPlayerCard(Deck* playerDeck);

	int getNumOfCards() { return this->cardsInHand.size(); }
	Card* getCard(int index) { return this->cardsInHand[index]; }
	// OBSERVER PATTERN: Add Card to Hand
	void addCard(Card* card);
	// OBSERVER PATTERN: Remove Card from Hand
	Card* removeCard(int index);

	
	string printHand();

	//Operator overload//////////////////////////
	const bool operator==(const string name);
	
};

