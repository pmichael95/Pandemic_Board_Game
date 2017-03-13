#pragma once

#include "CommonLibrary.h"
#include "Player.h"


using namespace std;

#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

class PlayerView {

	public: 
		PlayerView();
		~PlayerView();

		void printPlayerDisplay(Player* player) const;
		void clearPlayerDisplay();

	private:
};

#endif