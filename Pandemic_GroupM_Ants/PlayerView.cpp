
#include "PlayerView.h"
#include "MapView.h"
#include "CommonLibrary.h"

PlayerView::PlayerView() {

}

PlayerView::~PlayerView() { }


void PlayerView::printPlayerDisplay(Player* player) const{

	cout << " ===================================================================== " << endl;
	cout << "   Player #" << player->getId() + 1 << "- Location: " << player->getPawn()->getName() << endl;
	cout << "\n   " << player->getRole()->print() << endl;
	cout << "\n   " << player->printHand() << endl;
	cout << " ===================================================================== " << endl;
	
}

// Clear Player Display
void PlayerView::clearPlayerDisplay() {
	system("CLS");
}


//int main() {
//	MapView map;
//	PlayerView playerDisplay;
//
//	RoleCard* role = new RoleCard("Doctor", "White", "This is a test role card");
//
//	Card* event = new EventCard("AIRDROP", "Drop cure for one location");
//	Card* city = new CityCard("Montreal", (InfectType)0);
//	Card* epidemic = new EpidemicCard();
//	ReferenceCard* reference = new ReferenceCard();
//
//	CityNode* node = new CityNode("Toronto", (InfectType)0, false);
//
//	Player* player = new Player(0, reference);
//	player->setRole(role);
//	player->setPawn(node);
//
//	player->addCard(event);
//	player->addCard(city);
//	player->addCard(epidemic);
//
//	vector<CityNode*> cityList;
//
//	for (int i = 0; i < 48; i++) {
//		cityList.push_back(new CityNode());
//	}
//
//	map.updateMap(&cityList);
//	map.printMap();
//
//	cout << "     **  PLAYER SCREEN **" << endl;
//
//	playerDisplay.printPlayerDisplay(player);
//
//
//	int num;
//
//	cin >> num;
//
//	if (num == 0) {
//		map.clearScreen();
//		playerDisplay.clearPlayerDisplay();
//
//		map.printMap();
//		playerDisplay.printPlayerDisplay(player);
//	}
//
//
//	for (int i = 0; i < 48; i++) {
//		delete cityList.at(i);
//	}
//
//	delete role;
//	delete event;
//	delete city;
//	delete epidemic;
//	delete node;
//	delete reference;
//
//
//	system("PAUSE");
//	return 0;
//}