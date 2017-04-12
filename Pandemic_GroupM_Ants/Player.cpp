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

//Get and Set Functions////////////////////////////////////////////

void Player::setPawn(CityNode * position)
{
	this->pawn = position;
	Notify();
}

void Player::setRole(RoleCard * role)
{
	this->role = role;
	Notify();
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
			return cardIndex;
		}
	}
	return cardIndex;
}

bool Player::checkifPlayerHasCardAtIndex(string name, int index) {
	return *cardsInHand[index] == name;
}

//Prints cards in hand, and key selections to select from them.
void Player::displayPlayerCardOptions()
{
	for (int i = 0; i < cardsInHand.size(); i++) {
		cout << i << ") " << cardsInHand[i]->print() << endl;
	}
}

void Player::discardPlayerCard(Deck * playerDeck)
{
	cout << "\nPlayer " << id << " has too many cards in hand! Select one to discard:" << endl;
	this->displayPlayerCardOptions();
	int answer;

	// Input Tick for visual purposes 
	cout << "> ";

	// Check input
	while (!getIntInput(answer, 0, cardsInHand.size())) {}

	// Discard Card
	Card* card = this->removeCard(answer);
	if (card->getType() == "City") {
		delete card;
		card = nullptr;
	}
	else {
		playerDeck->discard(card);
	}
	cout << "Discarding Card\n" << endl;
}

void Player::addCard(Card * card)
{
	this->cardsInHand.push_back(card);
	Notify();
}

// OBSERVER PATTERN: Remove Card from Hand
Card* Player::removeCard(int index)
{
	if (index < cardsInHand.size() && index > -1) {
		Card* temp = this->cardsInHand[index];
		this->cardsInHand.erase(cardsInHand.begin() + index);

		Notify(); // Overriden Notify Function

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

const bool Player::operator==(const string name)
{
	if (*role == name) {
		return true;
	}
	else {
		return false;
	}
}
