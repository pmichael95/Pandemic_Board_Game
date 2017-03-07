#include "Player.h"

//PLAYER CLASS///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Constructors////////////////////////////////////////////
Player::Player() : id(0), pawn(nullptr), role(nullptr), reference(nullptr){}

Player::Player(int id, ReferenceCard* referenceCard) : id(id), reference(referenceCard) {}

Player::~Player()
{
	for (int i = 0; i < cardsInHand.size(); i++) {
		delete this->cardsInHand[i];
		this->cardsInHand[i] = nullptr;
	}
}


//Get and Set Functions/////////////////////////////////////
void Player::setPawn(CityNode * position)
{	this->pawn = position;	}

CityNode * Player::getPawn()
{	return this->pawn;	}

RoleCard * Player::getRole()
{	return this->role;	}

void Player::setRole(RoleCard* roleCard)
{	this->role = roleCard;	}

ReferenceCard * Player::getReferenceCard()
{	return this->reference;	}


//Card Functions/////////////////////////////////////////////
int Player::getNumOfCards()
{	return this->cardsInHand.size();	}

Card * Player::getCard(int index)
{	return this->cardsInHand[index];	}

void Player::addCard(Card* card)
{	this->cardsInHand.push_back(card);	}

Card* Player::removeCard(int index)
{
	if (index < cardsInHand.size() && index > -1) {
		Card* temp = this->cardsInHand[index];
		this->cardsInHand.erase(cardsInHand.begin() + index);
		return temp;
	}
	else
		return nullptr;
}
