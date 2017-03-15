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
	ReferenceCard* reference;
	RoleCard* role;

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
	void setPawn(CityNode* position) { this->pawn = position; }
	CityNode* getPawn() { return this->pawn; }

	int getId() { return id; }

	RoleCard* getRole() { return this->role; }
	void setRole(RoleCard* role) { this->role = role; }
	ReferenceCard* getReferenceCard() { return this->reference; }

	//Card Methods///////////////////////////////
	int getNumOfCards() { return this->cardsInHand.size(); }
	Card* getCard(int index) { return this->cardsInHand[index]; }
	void addCard(Card* card) { this->cardsInHand.push_back(card); }
	Card* removeCard(int index);
	string printHand();
};

