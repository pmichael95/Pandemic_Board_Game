#pragma once

#include "CommonLibrary.h"
#include "Map.h"

using namespace std;

#ifndef MAPVIEW_H
#define MAPVIEW_H

class MapView {

	public:
		// Constructor
		MapView();

		// Destructor
		~MapView();

		void updateMap(const vector<CityNode *> * cityList);
		void printMap();
		void clearScreen();

	private:
		string cityInfection[NUM_OF_CITIES];


};

#endif