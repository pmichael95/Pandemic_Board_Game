#pragma once

#include "CommonLibrary.h"
#include "Map.h"
#include "Markers.h"

using namespace std;

#ifndef MAPVIEW_H
#define MAPVIEW_H

class MapView {

	public:
		// Constructor
		MapView();

		// Destructor
		~MapView();

		// ============ MapView Methods ==============
		void updateMap(const vector<CityNode *> * cityList);  // Updates the map 
		void printMap(Markers* marker);  // Prints the map
		void clearScreen();  // Clears the MapView Screen

		string MapView::fillNumber(int number);  // Local function to fill in blank space for consistency

	private:
		string cityInfection[NUM_OF_CITIES];	// List of City Names
		string researchStationCities;			// List of cities with research stations
};

#endif