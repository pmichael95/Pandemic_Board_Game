#include "Cards.h"

//CARD CLASS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Default constructor
Card::Card() {
	this->type = "";
}

// Constructor that takes in a Type
Card::Card(string type) {
	this->type = type;
}

// Default destructor
Card::~Card() { }

// Setter to set the type of the Card
void Card::setType(string type) {
	this->type = type;
}

// Getter to return the type of the Card
string Card::getType() const {
	return this->type;
}




//DECK CLASS//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Deck::Deck()
{
	this->drawPile = deque<Card*>();
	this->discardPile = deque<Card*>();
}

Deck::Deck(string fileName)
{
	this->drawPile = deque<Card*>();
	this->discardPile = deque<Card*>();
	initialize(fileName);
	shuffleDeck();
}

Deck::~Deck()
{
	for (int i = 0; i < drawPile.size(); i++)
	{
		delete drawPile[i];
		drawPile[i] = nullptr;
	}
	for (int j = 0; j < discardPile.size(); j++)
	{
		delete discardPile[j];
		drawPile[j] = nullptr;
	}
}

deque<Card*> &Deck::getDrawPile()
{
	return this->drawPile;
}

deque<Card*> &Deck::getDiscardPile()
{
	return this->discardPile;
}

void Deck::initialize(string fileName)
{
	ifstream file;
	file.open(fileName);

	if (fileName == INFECTION_CARD_INITIAL_FILE)
	{
		cout << "Pulling the Infection Deck out of the box..." << endl;
		populateInfect(file);
	}
	else if (fileName == PLAYER_CARD_INITIAL_FILE)
	{
		cout << "Pulling the Player Deck out of the box..." << endl;
		populatePlayer(file);

	}
	else if (fileName == ROLE_CARD_INITIAL_FILE)
	{
		cout << "Pulling the Role Deck out of the box..." << endl;
		populateRole(file);
	}
	else
	{
		cout << "Invalid FileName.";
	}

	file.close();
}

void Deck::populatePlayer(ifstream& file)
{
	string type;
	if (file.is_open())
	{
		while (!file.eof())
		{
			string type;
			file >> type;
			if (type == "City")
			{
				int color;
				string city;
				file >> color >> ws;
				getline(file, city);
				Card *cityCard = new CityCard(city, (InfectType)color);
				addCard(cityCard);
			}
			else if (type == "Event")
			{
				string name;
				string description;
				file >> name >> ws;
				getline(file, description);
				Card *eventCard = new EventCard(name, description);
				addCard(eventCard);
			}
		}
	}
	else
		cout << "Invalid file configuration" << endl;
}

void Deck::populateInfect(ifstream& file)
{
	int color;
	string city;
	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> color >> ws;
			getline(file, city);

			Card *infectionCard = new InfectionCard(city, (InfectType)color);

			addCard(infectionCard);

		}
	}
	else
		cout << "Invalid file configuration" << endl;
}

void Deck::populateRole(ifstream& file)
{
	string title;
	string color;
	string description;
	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, title);
			getline(file, color);
			getline(file, description);

			Card *roleCard = new RoleCard(title, color, description);

			addCard(roleCard);

		}
	}
	else
		cout << "Invalid file configuration" << endl;
}

int Deck::cardsInDeck()
{
	return drawPile.size();
}

int random(int i)
{
	return rand() % i;
}

void Deck::shuffleDeck()
{
	srand(unsigned(time(0)));
	random_shuffle(this->getDrawPile().begin(), this->getDrawPile().end(), random);
}

void Deck::discardToDraw()
{
	srand(unsigned(time(0)));
	random_shuffle(this->getDiscardPile().begin(), this->getDiscardPile().end(), random);
	while (discardPile.size() > 0)
	{
		Card* card = discardPile.back();
		discardPile.pop_back();
		addCard(card);
	}
}

Card* Deck::drawFromTop()
{
	if (cardsInDeck() > 0)
	{
		Card* toReturn = drawPile.back();
		drawPile.pop_back();
		return toReturn;
	}
	//else
		//lose
}

Card* Deck::drawFromBottom()
{
	if (cardsInDeck() > 0)
	{
		Card* toReturn = drawPile.front();
		drawPile.pop_front();
		return toReturn;
	}
	//else
		//lose
}

void Deck::discard(Card* card)
{
	discardPile.push_back(card);
}

void Deck::addCard(Card* card)
{
	drawPile.push_back(card);
}



//INFECTION CARDS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Default constructor
InfectionCard::InfectionCard() : Card("Infection") {
	this->city = "";
}

// Constructor that sets all variables
InfectionCard::InfectionCard(string city, InfectType color) : Card("Infection"){
	this->city = city;
	this->color = color;
}

// Default destructor
InfectionCard::~InfectionCard() { }

// Setter for the city
void InfectionCard::setCity(string city) {
	this->city = city;
}

// Setter for the color
void InfectionCard::setColor(InfectType color) {
	this->color = color;
}

// Getter for the city
string InfectionCard::getCity() const {
	return this->city;
}

// Getter for the color as a string
string InfectionCard::getColorString() const {
	return infectTypeEnumToString(this->color); // Call the helper enumToString to get a string for the color
}

// Getter for the color as InfectType
InfectType InfectionCard::getColor() const {
	return this->color;
}

// Print implementation from Card
string InfectionCard::print() {
	string infectionPrint = (this->getType() + " card: " + this->getCity() + "(" + this->getColorString() + ")");

	return infectionPrint;
}





/***********************
---- EVENT CARDS ----
***********************/

// Default Event card constructor
EventCard::EventCard() : Card("Event") {
	this->name = "";
	this->desc = "";
}

// Constructor that sets all members
EventCard::EventCard(string name, string desc) : Card("Event"){
	this->name = name;
	this->desc = desc;
}

// Default destructor
EventCard::~EventCard() { }

// Setter for the name
void EventCard::setName(string name) {
	this->name = name;
}

// Setter for the description
void EventCard::setDesc(string desc) {
	this->desc = desc;
}

// Getter for the name
string EventCard::getName() const {
	return this->name;
}

// Getter for the description
string EventCard::getDesc() const {
	return this->desc;
}

// Print method from Card for Event cards
string EventCard::print() {
	string eventPrint = this->getType() + " card: " + this->getName() + " (Description: " + this->getDesc() + ")";

	return eventPrint;
}

/***********************/




/***********************
---- CITY CARDS ----
***********************/

// Default City card constructor
CityCard::CityCard() : Card("City") {
	this->city = "";
}

// Constructor that sets all members
CityCard::CityCard(string city, InfectType color) : Card("City") {
	this->city = city;
	this->color = color;
}

// Default destructor
CityCard::~CityCard() { }

// Setter for city
void CityCard::setCity(string city) {
	this->city = city;
}

// Setter for the color
void CityCard::setColor(InfectType color) {
	this->color = color;
}

// Getter for city
string CityCard::getCity() const {
	return this->city;
}

// Getter for the color as a string
string CityCard::getColorString() const {
	return infectTypeEnumToString(this->color);
}

// Getter for the color as a InfectType
InfectType CityCard::getColor() const {
	return this->color;
}

// Print method from Card for City cards
string CityCard::print() {

	string cityPrint = this->getType() + " card: " + this->getCity() + "(" + this->getColorString() + ")";

	return cityPrint;
}

/***********************/





/***********************
---- EPIDEMIC CARDS ----
***********************/

// Default constructor
EpidemicCard::EpidemicCard() : Card("Epidemic") {
	this->desc = "1. INCREASE \nMove the Infection Rate Indicator up by 1.\n\n"
		"2. INFECT \nDraw a card off the bottom of the Infection Draw Pile and infect the indicated city with 3 cubes.\nDiscard the card.\n\n"
		"3. INTENSIFY \nShuffle the Infection Discard Pile and place it on top of the Infection Draw Pile.";
}

// Default destructor
EpidemicCard::~EpidemicCard() { }

// Setter for the description
void EpidemicCard::setDesc(string desc) {
	this->desc = desc;
}

// Getter for the description
string EpidemicCard::getDesc() const {
	return this->desc;
}

// Print method from Card for Epidemic cards
string EpidemicCard::print() {

	string epidemicPrint = (this->getType() + " card");

	return epidemicPrint;
}

string EpidemicCard::printDescription() {
	return ("Description: \n" + this->getDesc());
}

/***********************/




/*
* ROLE CLASS IMPLEMENTATION
*/

// Default constructor
RoleCard::RoleCard() : Card("Role") {
	this->name = "";
	this->color = "";
	this->desc = "";
}

// Constructor that populates all variables
RoleCard::RoleCard(string name, string color, string desc) : Card("Role") {
	this->name = name;
	this->color = color;
	this->desc = desc;
}

// Default destructor
RoleCard::~RoleCard() { }

// Getter for the name
string RoleCard::getName() const {
	return this->name;
}

// Getter for the color
string RoleCard::getColor() const {
	return this->color;
}

// Getter for the description
string RoleCard::getDesc() const {
	return this->desc;
}

// Setter for the name
void RoleCard::setName(string name) {
	this->name = name;
}

// Setter for the color
void RoleCard::setColor(string color) {
	this->color = color;
}

// Setter for the description
void RoleCard::setDesc(string desc) {
	this->desc = desc;
}

// Implementation for print (for the role)
string RoleCard::print() {

	string rolePrint = (this->getType() + ": " + this->getName() + "\n" + "      - Description: " + this->getDesc());

	return rolePrint;
}



/*
* REFERENCE CARD IMPLEMENTATION
*/

// Default constructor that initializes the reference card
ReferenceCard::ReferenceCard() : Card("Reference") {
	this->reference = "\n== BASIC ACTIONS ==\n"
		"\n* Drive (or Ferry)"
		"\nMove your pawn to an adjacent City.\n"
		"\n* Direct Flight"
		"\nDiscard a card to move your pawn to the City pictured on it.\n"
		"\n* Charter Flight"
		"\nDiscard the card showing your current City and move to any City on the board.\n"
		"\n* Shuttle Flight"
		"\nMove to a City containing a Research Station if your pawn is in a City containing one.\n"
		"\n== SPECIAL ACTIONS==\n"
		"\n* Build a Research Station"
		"\nDiscard the card showing your current City to build a Research Station there.\n"
		"\n* Discover a Cure"
		"\nDiscard 5 cards of the same color to cure the disease of that color.\nYour pawn must be in a City containing a Research Station.\n"
		"\n* Treat Disease"
		"\nRemove a disease cube from the City your pawn occupies. If the cure has been found, remove ALL cubes of that color from the City.\n"
		"\n* Share Knowledge"
		"\nPass a card from one Player to another.\nBother Players' pawns must be in the City pictured on the card that is passed.\n";
}

// Default destructor
ReferenceCard::~ReferenceCard() { }

// Getter for the reference card
string ReferenceCard::getReferenceCard() const {
	return this->reference;
}

// Print implementation to output the reference card
string ReferenceCard::print() {

	string referencePrint = (this->getType() + " card: " + this->getReferenceCard());
	return referencePrint;
}