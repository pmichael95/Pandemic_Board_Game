#pragma once

#include "CommonLibrary.h"
#include "Map.h"
#include "Markers.h"
#include "Observer.h"

using namespace std;

#ifndef MAPVIEW_H
#define MAPVIEW_H

class MapView : public Observer {

	public:
		// Constructor
		MapView(Markers* markers, GameMap* map);

		// Destructor
		~MapView();

		// Overriden Observer Function
		void Update();

		// ============ MapView Methods ==============
		void updateMap(const vector<CityNode *> * cityList);  // Updates the map 
		void printMap();									  // Prints the map
		void clearScreen();									  // Clears the MapView Screen

		string MapView::fillNumber(int number);  // Local function to fill in blank space for consistency

	private:
		string cityInfection[NUM_OF_CITIES];	// List of City Names
		string researchStationCities;			// List of cities with research stations

		// Subject to be attached
		Markers* subjMarker;
		GameMap* subjMap;
};

#endif