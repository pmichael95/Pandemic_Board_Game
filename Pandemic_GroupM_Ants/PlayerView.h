#pragma once

#include "CommonLibrary.h"
#include "Player.h"


using namespace std;

#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

class PlayerView {

	public: 
		// Constructor
		PlayerView();

		// Destructor
		~PlayerView();

		// ========== Playerview Functions =============
		void printPlayerDisplay(Player* player) const; // Prints the player view
		void clearPlayerDisplay();  // Clears the player view

};

#endif