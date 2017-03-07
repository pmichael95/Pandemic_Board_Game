#include "Markers.h"


//MARKERS CLASS/////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Constructors///////////////////////////////////////////
Markers::Markers() : researchStations(NUM_OF_RESEARCH_STATIONS), outbreakCounter(0), infectionRatePosition(&INFECTION_RATE[0])
{
	std::fill_n(this->diseaseCubes, NUM_OF_DISEASES, NUM_OF_DISEASE_CUBES_PER_TYPE);
	std::fill_n(this->cureMarkers, NUM_OF_DISEASES, false);
}

Markers::~Markers() {}


//Get and Set/////////////////////////////////////////////

// Research Stations
int Markers::getNumOfResearchStations()
{
	return this->researchStations;
}

bool Markers::useResearchStation()
{
	if (this->researchStations > 0) {
		this->researchStations--;
		return true;
	}
	return false;
}


// Disease Cubes
int Markers::getNumOfDiseaseCubes(InfectType color)
{
	return this->diseaseCubes[color];
}

bool Markers::useDiseaseCube(InfectType color)
{
	if (this->diseaseCubes[color] > 0) {
		this->diseaseCubes[color]--;
		return true;
	}
	return false;
}


//Outbreak Counter
int Markers::getOutbreakCounter()
{
	return this->outbreakCounter;
}

void Markers::increaseOutbreakCounter()
{
	this->outbreakCounter++;
}


//Infection Rate
int Markers::getInfectionRate()
{
	return *this->infectionRatePosition;
}

void Markers::increaseInfectRate()
{
	this->infectionRatePosition++;
}


//Cure Marker
bool Markers::getCureMarker(InfectType infection)
{
	return this->cureMarkers[infection];
}

void Markers::setCureMarkerToTrue(InfectType infection)
{
	this->cureMarkers[infection] = true;
}


