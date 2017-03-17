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
	delete reference;
	reference = nullptr;
	delete role;
	role = nullptr;
}

//Card Functions////////////////////////////////////////////
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

string Player::printHand() {
	string hand = "Hand: \n";

	for (int i = 0; i < cardsInHand.size(); i++) {
		hand.append("      - " + cardsInHand.at(i)->print() + "\n");
	}

	return hand;

}