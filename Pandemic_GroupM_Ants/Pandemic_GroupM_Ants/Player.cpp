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

void Player::addExtraPlannerCard(Card* card)
{
	extraPlannerCard = card;
}

Card* Player::useExtraPlannerCard()
{
	Card* card = extraPlannerCard;
	extraPlannerCard = nullptr;
	return card;
}

//Card Functions////////////////////////////////////////////
//checks if player is holding a specific card and if true, returns the index position of the card in the players hand
int Player::checkifPlayerHasCard(string name)
{
	int cardIndex = -1;
	for (int i = 0; i < cardsInHand.size(); i++)
	{
		if (*cardsInHand[i] == name)
		{
			cardIndex = i;
			break;
		}
	}
	return cardIndex;
}

//Prints cards in hand, and key selections to select from them.
void Player::displayPlayerCardOptions()
{
	for (int i = 0; i < cardsInHand.size(); i++) {
		cout << i << ") " << cardsInHand[i]->print() << endl;
	}
}

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

const bool Player::operator==(const string name) const
{
	if (*role == name) {
		return true;
	}
	else {
		return false;
	}
}
