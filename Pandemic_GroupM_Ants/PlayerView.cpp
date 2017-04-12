
#include "PlayerView.h"
#include "MapView.h"
#include "CommonLibrary.h"

// Constructor
PlayerView::PlayerView(vector<Player*>* player) {

	for (int i = 0; i < player->size(); i++) {
		this->subjPlayers.push_back(player->at(i));
		this->subjPlayers.at(i)->Attach(this);
	}
}

// Destructor
PlayerView::~PlayerView() { 
	for (int i = 0; i < subjPlayers.size(); i++) {
		this->subjPlayers.at(i)->Detach(this);
	}
}

// Overriden Observer Pattern: Update()
void PlayerView::Update() {
	printPlayerDisplay(this->playerIndex);
}

// Print PLayerView Function
void PlayerView::printPlayerDisplay(int index) const{

	cout << " ===================================================================== " << endl;
	cout << "   Player #" << subjPlayers.at(index)->getId() + 1 << "- Location: " << subjPlayers.at(index)->getPawn()->getName() << endl;
	cout << "\n   " << subjPlayers.at(index)->getRole()->print() << endl;
	cout << "\n   " << subjPlayers.at(index)->printHand() << endl;
	cout << " ===================================================================== " << endl << endl;
	
}

// Clear Player Display
void PlayerView::clearPlayerDisplay() {
	system("CLS");
}
