#pragma once

#include "CommonLibrary.h"

//MARKERS CLASS////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
class Markers
{
	//Attributes///////////////////////////////////////
	int researchStations;
	int diseaseCubes[NUM_OF_DISEASES];
	int outbreakCounter;
	const int* infectionRatePosition;
	CureStatus cureMarkers[NUM_OF_DISEASES];

public:
	//Constructors/////////////////////////////////////
	Markers();
	~Markers();

	//Get and Set///////////////////////////////////////
	int getNumOfResearchStations() { return this->researchStations; }
	bool useResearchStation();

	int getNumOfDiseaseCubes(InfectType color) { return this->diseaseCubes[color]; }
	bool useDiseaseCube(InfectType color);

	int getOutbreakCounter() { return this->outbreakCounter; }
	void increaseOutbreakCounter() { this->outbreakCounter++; }

	int getInfectionRate() { return *this->infectionRatePosition; }
	void increaseInfectRate() { this->infectionRatePosition++; }

	CureStatus getCureMarker(InfectType infection) { return this->cureMarkers[infection]; }
	void cureDiseaseUpdateMarker(InfectType infection) { this->cureMarkers[infection] = cured; }
	void eradicateDiseaseUpdateMarker(InfectType infection) { this->cureMarkers[infection] = eradicated; }

};

