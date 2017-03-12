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

deque<Card*> Deck::getDrawPile()
{
	return this->drawPile;
}

deque<Card*> Deck::getDiscardPile()
{
	return this->discardPile;
}

void Deck::initialize(string fileName)
{
	ifstream file;
	file.open(fileName);

	if (fileName == "Infection.txt")
	{
		cout << "Populating Infection Deck...";
		populateInfect(file);
		cout << "Populating Infection Deck Complete.";
	}
	else if (fileName == "Player.txt")
	{
		cout << "Populating Player Deck...";
		populatePlayer(file);
		cout << "Populating Player Deck Complete.";
	}
	else if (fileName == "Role.txt")
	{
		cout << "Populating Role Deck...";
		populateRole(file);
		cout << "Populating Role Deck Complete.";
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
				//getline(file, description);
				Card *eventCard = new EventCard(name, "");
				addCard(eventCard);
			}
			else if (type == "Epidemic")
			{
				Card *epidemicCard = new EpidemicCard();
				addCard(epidemicCard);
			}

			cout << "ADDED CARD " << endl;
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

			cout << "ADDED CARD " << city << endl;
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

			cout << "ADDED CARD " << endl;
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
InfectionCard::InfectionCard() {
	this->city = "";
	this->setType("infection");
}

// Constructor that sets all variables
InfectionCard::InfectionCard(string city, InfectType color) {
	this->city = city;
	this->color = color;
	this->setType("infection");
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
void InfectionCard::print() {
	cout << "== Printing out a " << this->getType() << " card. ==" << endl;
	cout << "City: " << this->getCity() << endl;
	cout << "Color: " << this->getColorString() << endl;
}





/***********************
---- EVENT CARDS ----
***********************/

// Default Event card constructor
EventCard::EventCard() {
	this->name = "";
	this->desc = "";
}

// Constructor that sets all members
EventCard::EventCard(string name, string desc) {
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
void EventCard::print() {
	cout << "== Printing out a " << this->getType() << " card. ==" << endl;
	cout << "Name: " << this->getName() << endl;
	cout << "Description: " << this->getDesc() << endl;
}

/***********************/




/***********************
---- CITY CARDS ----
***********************/

// Default City card constructor
CityCard::CityCard() {
	this->city = "";
}

// Constructor that sets all members
CityCard::CityCard(string city, InfectType color) {
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
void CityCard::print() {
	cout << "== Printing out a " << this->getType() << " card. ==" << endl;
	cout << "City: " << this->getCity() << endl;
	cout << "Color: " << this->getColorString() << endl;
}

/***********************/





/***********************
---- EPIDEMIC CARDS ----
***********************/

// Default constructor
EpidemicCard::EpidemicCard() {
	this->desc = "Epidemic";
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
void EpidemicCard::print() {
	cout << "== Printing out a " << this->getType() << " card. ==" << endl;
	cout << "Description: " << this->getDesc() << endl;
}

/***********************/




/*
* ROLE CLASS IMPLEMENTATION
*/

// Default constructor
RoleCard::RoleCard() {
	this->name = "";
	this->color = "";
	this->desc = "";
	this->setType("role");
}

// Constructor that populates all variables
RoleCard::RoleCard(string name, string color, string desc) {
	this->name = name;
	this->color = color;
	this->desc = desc;
	this->setType("role");
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
void RoleCard::print() {
	cout << "== Printing out a " << this->getType() << " card. ==" << endl;
	cout << "Name: " << this->getName() << endl;
	cout << "Color: " << this->getColor() << endl;
	cout << "Description: " << this->getDesc() << endl;
}



/*
* REFERENCE CARD IMPLEMENTATION
*/

// Default constructor that initializes the reference card
ReferenceCard::ReferenceCard() {
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

	this->setType("reference");
}

// Default destructor
ReferenceCard::~ReferenceCard() { }

// Getter for the reference card
string ReferenceCard::getReferenceCard() const {
	return this->reference;
}

// Print implementation to output the reference card
void ReferenceCard::print() {
	cout << "== Printing out a " << this->getType() << " card. ==" << endl;
	cout << this->getReferenceCard() << endl;
}