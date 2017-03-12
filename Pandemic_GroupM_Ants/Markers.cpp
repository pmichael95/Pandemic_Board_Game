#include "Markers.h"


//MARKERS CLASS/////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Constructors///////////////////////////////////////////
Markers::Markers() : researchStations(NUM_OF_RESEARCH_STATIONS), outbreakCounter(0), infectionRatePosition(&INFECTION_RATE[0])
{
	std::fill_n(this->diseaseCubes, NUM_OF_DISEASES, NUM_OF_DISEASE_CUBES_PER_TYPE);
	std::fill_n(this->cureMarkers, NUM_OF_DISEASES, notCured);
}

Markers::~Markers() {}


//Get and Set/////////////////////////////////////////////
bool Markers::useResearchStation()
{
	if (this->researchStations > 0) {
		this->researchStations--;
		return true;
	}
	return false;
}

bool Markers::useDiseaseCube(InfectType color)
{
	if (this->diseaseCubes[color] > 0) {
		this->diseaseCubes[color]--;
		return true;
	}
	return false;
}