
#include "PlayerView.h"
#include "MapView.h"
#include "CommonLibrary.h"

// Constructor
PlayerView::PlayerView() {
}

// Destructor
PlayerView::~PlayerView() { }

// Print PLayerView Function
void PlayerView::printPlayerDisplay(Player* player) const{

	cout << " ===================================================================== " << endl;
	cout << "   Player #" << player->getId() + 1 << "- Location: " << player->getPawn()->getName() << endl;
	cout << "\n   " << player->getRole()->print() << endl;
	cout << "\n   " << player->printHand() << endl;
	cout << " ===================================================================== " << endl << endl;
	
}

// Clear Player Display
void PlayerView::clearPlayerDisplay() {
	system("CLS");
}
