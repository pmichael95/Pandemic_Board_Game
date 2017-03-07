#include "Map.h"

//CITY NODE Class Definitions////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Constructors////////////////////////////////
CityNode::CityNode() : name(""), infectionLevel(), researchStation(false) {}

CityNode::CityNode(string name, InfectType area, bool researchStation) : name(name), area(area), infectionLevel(), researchStation(researchStation) {}

CityNode::~CityNode(){}


//Get and Set//////////////////////////////////
string CityNode::getName()
{	return this->name;	}

InfectType CityNode::getArea()
{	return this->area;	}

int CityNode::getInfectionLevel(InfectType infection)
{	return this->infectionLevel[infection];	}

void CityNode::increaseInfectionLevel(InfectType infection)
{	this->infectionLevel[infection]++;	}

bool CityNode::hasResearchStation()
{	return this->researchStation;	}

void CityNode::addResearchStation()
{	this->researchStation = true;	}

vector<CityNode*> CityNode::getConnections()
{	return this->connections;	}

void CityNode::addConnection(CityNode* city)
{	this->connections.push_back(city);	}




//GAME MAP Class Definitions/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Constructors//////////////////////////////////
GameMap::GameMap() {}

GameMap::GameMap(string filename) {
	loadStartingMap(filename);
	this->head = this->cityList[0];
}

GameMap::~GameMap()
{
	for (int i = 0; i < cityList.size(); i++) {
		delete this->cityList[i];
		this->cityList[i] = nullptr;
	}
}


//Get and Set/////////////////////////////////////
CityNode* GameMap::getHead()
{	return this->head;	}

CityNode* GameMap::getCity(string name)
{
	for (int i = 0; i < this->cityList.size(); i++) {
		if (this->cityList[i]->getName() == name)
			return this->cityList[i];
	}
	return nullptr;
}


//Helper Functions//////////////////////////////////////////////////////
void GameMap::loadStartingMap(string filename)
{
	char datatype;
	string name, garbage;
	int zone;
	CityNode* city;
	int connectIndex1, connectIndex2;

	ifstream file;
	file.open(filename);
	if (!file.good()) {
		cout << "Invalid file location: map" << endl;
		return;
	}

	while (!file.eof()) {
		file >> datatype;
		//Identifies cities and adds them to the map graph
		if (datatype == 'C') {
			file >> zone;
			file.ignore(1);
			getline(file, name);
			city = new CityNode(name, (InfectType)zone);
			this->cityList.push_back(city);

		}
		//Identifies edges and adds them to the map graph
		else if (datatype == 'e') {
			file >> connectIndex1 >> connectIndex2;
			file.ignore();
			this->cityList[connectIndex1]->addConnection(this->cityList[connectIndex2]);
			this->cityList[connectIndex2]->addConnection(this->cityList[connectIndex1]);
		}
		else {
			getline(file, garbage);
		}
	}
}
