#pragma once

#include "CommonLibrary.h"

/*
* CARD CLASS
* - Used to create "physical" Card objects that the Deck will hold.
* - This is a Base class, individual types of cards will be created in its Derived classes.
*/

class Card {
private:
	string type; // The type of card - Role, Reference, Infection, or Player
public:
	Card(); // Default constructor
	Card(string type); // Constructor that takes in a Type
	virtual ~Card(); // Default destructor (virtual)
	virtual void print() = 0; // Virtual function that will be used to print out the Card object in its derived classes
	void setType(string type); // Sets the type of the Card
	string getType() const; // Returns the type of the Card object
};




/*
* GENERIC DECK CLASS
-> Holds a vector of cards (Card objects).
*/


class Deck
{
private:
	deque<Card*> drawPile;
	deque<Card*> discardPile;

	void initialize(string fileName);
	void populatePlayer(ifstream& file);
	void populateInfect(ifstream& file);
	void populateRole(ifstream& file);

public:
	Deck();
	Deck(string fileName);
	~Deck();

	deque<Card*> getDrawPile();
	deque<Card*> getDiscardPile();

	void shuffle();
	void discardToDraw();
	Card* drawFromTop();
	Card* drawFromBottom();		//Infection Only
	void discard(Card* card);
	void addCard(Card* card);
};




/*
* INFECTION CARD CLASS
*/

class InfectionCard : public Card {
private:
	string city; // The city infected
	InfectType color; // Based off an enum of InfectType, we get the color
public:
	InfectionCard(); // Default constructor
	InfectionCard(string city, InfectType color); // Constructor setting all variables
	~InfectionCard(); // Default destructor
	void setCity(string city); // Setter for the city
	void setColor(InfectType color); // Setter for the color
	string getCity() const; // Getter for the city
	string getColorString() const; // Getter for the color as a string
	InfectType getColor() const; // Returns an InfectType for the color
	void print(); // Print method implementation from Card
};



// -------- EVENT CARDS
class EventCard : public Card {
private:
	string name; // Name for the Event Card
	string desc; // Description for the Event Card
public:
	EventCard(); // Default constructor
	EventCard(string name, string desc); // Constructor that sets all variables
	~EventCard(); // Default destructor
	void setName(string name); // Setter for the name
	void setDesc(string desc); // Setter for the description
	string getName() const; // Getter for the Event name
	string getDesc() const; // Getter for the Event description
	void print(); // Implementation for print from Card
};




// -------- CITY CARDS
class CityCard : public Card {
private:
	string city; // City name
	InfectType color; // Color 
public:
	CityCard(); // Default constructor
	CityCard(string city, InfectType color); // Constructor that sets all variables
	~CityCard(); // Default destructor
	void setCity(string city); // Setter for the city
	void setColor(InfectType color); // Setter for the color
	string getCity() const; // Getter for the city
	string getColorString() const; // Getter for the color as a string
	InfectType getColor() const; // Getter for the color as an InfectType
	void print(); // Implementation for print from Card
};




// -------- EPIDEMIC CARDS
class EpidemicCard : public Card {
public:
	string desc; // Description (info) for the Epidemic Card
public:
	EpidemicCard(); // Default constructor
	EpidemicCard(string desc); // Constructor that sets the description
	~EpidemicCard(); // Default destructor
	void setDesc(string desc); // Setter for the description
	string getDesc() const; // Getter for the description
	void print(); // Implementation of print from Card
};




/*
* ROLE CLASS
* - Creates a Card of type Role
*/

class RoleCard : public Card {
private:
	string name; // Name of the role 
	string color; // Color for the role
	string desc; // Description for the role
public:
	RoleCard(); // Default constructor
	RoleCard(string name, string color, string desc); // Constructor that sets all member variables
	~RoleCard(); // Default destructor
	string getName() const; // Returns the role name
	string getColor() const; // Returns the role color
	string getDesc() const; // Returns the role description
	void setName(string name); // Sets the role name
	void setColor(string color); // Sets the role color
	void setDesc(string desc); // Sets the role description
	void print(); // Prints out the card (inherited)
};




/*
* REFERENCE CARD
* - Holds the Reference card for all players
*/

class ReferenceCard : public Card {
private:
	string reference; // The reference card
public:
	ReferenceCard(); // Default constructor
	~ReferenceCard(); // Default destructor
				  // NOTE: Do not need any other constructor since the reference card is always the same.
	string getReferenceCard() const; // Return the reference card
	void print(); // Print implementation (from Card)
};