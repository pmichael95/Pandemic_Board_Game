#pragma once

#include "CommonLibrary.h"

//City Node Class //////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CityNode
{
	//Attributes//////////////////////////////
	string name;
	InfectType area;
	int infectionLevel[NUM_OF_DISEASES];
	vector<CityNode*> connections;
	bool researchStation;

	//Serialize//////////////////
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive& ar, const unsigned version) {
		ar & name & area & infectionLevel & researchStation & connections;
	}

public:
	//Constructors////////////////////////////
	CityNode();
	CityNode(string name, InfectType area, bool researchStation = false);
	~CityNode();

	//Get and Set////////////////////////////
	string getName() {	return this->name;	}
	
	InfectType getArea() { return this->area; }

	int getInfectionLevel(InfectType infection) { return this->infectionLevel[infection]; }
	void increaseInfectionLevel(InfectType infection) { this->infectionLevel[infection]++; }
	void reduceInfectionLevel(InfectType infection) { this->infectionLevel[infection]--; }
	
	bool hasResearchStation() { return this->researchStation; }
	void addResearchStation() { this->researchStation = true; }
	
	vector<CityNode*> getConnections() { return this->connections; }
	void addConnection(CityNode* city) { this->connections.push_back(city); }
};

//GAME MAP CLASS///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GameMap
{
	//Attributes/////////////////////////////////////
	CityNode* head;
	vector<CityNode*> cityList;

	//Serialize/////////////////////////
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive& ar, const unsigned version) {
		ar.template register_type<CityNode>();
		ar & head & cityList;
	}

public:
	//Constructors///////////////////////////////////
	GameMap();
	GameMap(string filename);
	~GameMap();

	//Get and Set////////////////////////////////////
	CityNode* getHead() { return this->head; }

	CityNode* getCity(string name);

	vector<CityNode*> * getCityList();

private:
	//Helper Functions///////////////////////////////
	void loadStartingMap(string filename);
};

