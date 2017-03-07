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
	bool cureMarkers[NUM_OF_DISEASES];

public:
	//Constructors/////////////////////////////////////
	Markers();
	~Markers();

	//Get and Set///////////////////////////////////////
	int getNumOfResearchStations();
	bool useResearchStation();

	int getNumOfDiseaseCubes(InfectType color);
	bool useDiseaseCube(InfectType color);

	int getOutbreakCounter();
	void increaseOutbreakCounter();

	int getInfectionRate();
	void increaseInfectRate();

	bool getCureMarker(InfectType infection);
	void setCureMarkerToTrue(InfectType infection);

};

