
#include "MapView.h"
#include "CommonLibrary.h"

using namespace std;


// Constructor
MapView::MapView(Markers* markers, GameMap* map) {
	this->subjMarker = markers;
	this->subjMarker->Attach(this);

	this->subjMap = map;
	this->subjMap->Attach(this);

	for (int i = 0; i < map->getNumberOfCities(); i++) {
		this->subjMap->getCity(i)->Attach(this);
	}
}

// Destructor
MapView::~MapView() { 
	this->subjMarker->Detach(this);
	
	for (int i = 0; i < subjMap->getNumberOfCities(); i++) {
		this->subjMap->getCity(i)->Detach(this);
	}

	this->subjMap->Detach(this);

}

// OBSERVER PATTERN: Update 
void MapView::Update() {
	//updateMap(subjMap->getCityList());
	printMap();
}

// ============ Print Map Function ====================
void MapView::printMap() {

	updateMap(subjMap->getCityList());

	cout << "\n ======================================================================================================== PANDEMIC MAP ================================================================================================= " << endl;
	cout << "                                                                                         ----------------------------------------------    " << endl;
	cout << "                                                                                        |  Infection Cubes [Yellow, Red, Blue, Black]  |   " << endl;
	cout << "                                                                                        |            [R-S] = Research Station          |   " << endl;
	cout << "                                                                                         -------------------- Legend ------------------ \n" << endl;
	
	// MAP: First Line
	cout << "                                                                        London          Essen       St. Pertersberg                    Moscow                                           Beijing         Seoul        " << endl;
	cout << "                                                           --------- " << cityInfection[12] << " -- " << cityInfection[21] << " -- " << cityInfection[32] << " ----------------- " << cityInfection[41] << "                                     " << cityInfection[35] << " -- " << cityInfection[23] << endl;
	cout << "                                                          |              " << mapResearchStation[12] << "    \\     " << mapResearchStation[21] << "     \\      " << mapResearchStation[32] << "            |             " << mapResearchStation[41] << "                                           " << mapResearchStation[35] << "     /     " << mapResearchStation[23] << "       " << endl;
	cout << "                                                          |                |       \\      |        \\                      |               |                                               |      /        |          " << endl;
	cout << "                                                          |                |        \\     |         \\                     |               |                                               |     /         |           " << endl;
	
	// MAP: Second Line
	cout << "     San Fransisco      Chicago        Montreal        New York         Madrid          Paris           Milan             |               |                                            Shanghai         Tokyo        " << endl;
	cout << " ----" << cityInfection[8] << " -- " << cityInfection[3] << " -- " << cityInfection[7] << " -- " << cityInfection[6] << " -- " << cityInfection[13] << " -- " << cityInfection[20] << " -- " << cityInfection[31] << "         |               |                                          " << cityInfection[36] << " -- " << cityInfection[14] << "----" << endl;
	cout << "    /   " << mapResearchStation[8] << "       /    " << mapResearchStation[3] << "   \\       " << mapResearchStation[7] << "  \\       " << mapResearchStation[6] << "            " << mapResearchStation[13] << "    \\     " << mapResearchStation[20] << "           " << mapResearchStation[31] << "    \\        |               |                                             " << mapResearchStation[36] << "          " << mapResearchStation[14] << "        " << endl;
	cout << "   /      |       /        |       \\              \\       |                |       \\      |                       \\       |               |                                               |    \\          |               " << endl;
	cout << "  /       |     /          |         \\              \\     |                |        \\     |                        \\      |               |                                               |     \\         |             " << endl;
	
	// MAP: Third Line
	cout << "     Los Angeles           |            Atlanta       Washington           |           Algiers                         Istanbul         Tehran                                            |      \\      Osaka        " << endl;
	cout << "     " << cityInfection[9] << "          |         " << cityInfection[0] << " -- " << cityInfection[2] << "          |         " << cityInfection[22] << " -----------------  " << cityInfection[34] << "    " << cityInfection[46] << " --------                                |       \\  " << cityInfection[24] << endl;
	cout << "    /   " << mapResearchStation[9] << "              |             " << mapResearchStation[0] << "  \\       " << mapResearchStation[2] << "              |            " << mapResearchStation[22] << "                     /     " << mapResearchStation[34] << "      /    " << mapResearchStation[46] << "             |                               |        \\    " << mapResearchStation[24] << "        " << endl;
	cout << "   /      |                |                      \\       |                |              |                     /         |      /        |               |                               |         \\     |            " << endl;
	cout << "  /       |                |                        \\     |                |              |                   /           |    /          |               |                               |          \\    |            " << endl;
	
	// MAP: Forth Line
	cout << "          |           Mexico City                       Miami              |              |             Cairo          Baghdad         Karachi          Delhi           Kokata        Hong Kong         Taipei     " << endl;
	cout << "           --------- " << cityInfection[5] << " ------------------ " << cityInfection[1] << "          |              ---------- " << cityInfection[33] << " -- " << cityInfection[42] << " -- " << cityInfection[47] << " -- " << cityInfection[44] << " -- " << cityInfection[38] << " -- " << cityInfection[27] << " -- " << cityInfection[25] << endl;
	cout << "                         " << mapResearchStation[5] << "   \\                      " << mapResearchStation[1] << "              |                            " << mapResearchStation[33] << "  \\        " << mapResearchStation[42] << "      /    " << mapResearchStation[47] << "      /     " << mapResearchStation[44] << "      /    " << mapResearchStation[38] << "      /   " << mapResearchStation[27] << "    \\      " << mapResearchStation[25] << "           " << endl;
	cout << "                           |       --------------         |                |                              |       \\       |      /        |      /         |      /        |      /       |        \\      |        /  " << endl;
	cout << "                           |                     \\        |                |                              |         \\     |    /          |    /           |    /          |    /         |          \\    |       /    " << endl;
	
	// MAP: Fifth Line
	cout << "                         Lima                      \\    Bogota         Sao Paula         Lagos         Khartoum         Riyadh          Mumbai          Chennai         Bangkok    Ho Chi Minh City     Manila   /  " << endl;
	cout << "                     " << cityInfection[10] << " ------------------ " << cityInfection[4] << " -- " << cityInfection[11] << " -- " << cityInfection[18] << " -- " << cityInfection[29] << "    " << cityInfection[42] << "    " << cityInfection[45] << " -- " << cityInfection[39] << " -- " << cityInfection[37] << " -- " << cityInfection[26] << " -- " << cityInfection[15] << endl;
	cout << "                         " << mapResearchStation[10] << "                          " << mapResearchStation[4] << "            " << mapResearchStation[11] << "           " << mapResearchStation[18] << "      /   " << mapResearchStation[29] << "           " << mapResearchStation[42] << "           " << mapResearchStation[45] << "            " << mapResearchStation[39] << "           " << mapResearchStation[37] << "     /    " << mapResearchStation[26] << "           " << mapResearchStation[15] << "         " << endl;
	cout << "                           |                              |                |               |      /       |                                                |               |      /                       |         /     " << endl;
	cout << "                           |                              |                |               |    /         |                                                |               |     /                        |        /   " << endl;
	
	// MAP: Sixth Line
	cout << "                        Santiago                     Buenos Aires          |           Kinshasa      Johannesburg                                          |            Jakarta                         Sydney    /        " << endl;
	cout << "                     " << cityInfection[17] << "                    " << cityInfection[19] << " ---------          " << cityInfection[30] << " -- " << cityInfection[40] << "                                          --------- " << cityInfection[28] << " ------------------ " << cityInfection[16] << endl;
	cout << "                         " << mapResearchStation[17] << "                          " << mapResearchStation[19] << "                            " << mapResearchStation[30] << "           " << mapResearchStation[40] << "                                                           " << mapResearchStation[28] << "                           " << mapResearchStation[16] << "" << endl;
	cout << endl;

	// Printing Marker Status
	cout << "\n             ------------------------------------------------------------------------------------------------ MARKERS -----------------------------------------------------------------------------  " << endl;
	cout << "                                                 Disease Status    Yellow Disease: " << cureStatusEnumToString(this->subjMarker->getCureMarker((InfectType)0)) << "  |    Cubes Left    Yellow: " << fillNumber(this->subjMarker->getNumOfDiseaseCubes((InfectType)0)) << "  |            Infection Outbreak: " << this->subjMarker->getOutbreakCounter() << endl;
	cout << "                                                ----------------      Red Disease: " << cureStatusEnumToString(this->subjMarker->getCureMarker((InfectType)1)) << "  |   ------------      Red: " << fillNumber(this->subjMarker->getNumOfDiseaseCubes((InfectType)1)) << "  |               Infecttion Rate: " << this->subjMarker->getInfectionRate() << endl;
	cout << "                                                                     Blue Disease: " << cureStatusEnumToString(this->subjMarker->getCureMarker((InfectType)2)) << "  |                    Blue: " << fillNumber(this->subjMarker->getNumOfDiseaseCubes((InfectType)2)) << "  |    Research Station Remaining: " << this->subjMarker->getNumOfResearchStations() << endl;
	cout << "                                                                    Black Disease: " << cureStatusEnumToString(this->subjMarker->getCureMarker((InfectType)3)) << "  |                   Black: " << fillNumber(this->subjMarker->getNumOfDiseaseCubes((InfectType)3)) << "  |    Research Station Locations: " << researchStationCities << endl;
	cout << " ======================================================================================================================================================================================================================= \n\n" << endl;

}


// Fills in the number for printing consistency
string MapView::fillNumber(int number) {
	if (number < 10)
		return " " + to_string(number) ;
	else
		return to_string(number);
}

// Update map for the Infection Rate on each city
void MapView::updateMap(const vector<CityNode *> * cityList) {

	string temp;
	researchStationCities = "";
	
	// Creates a string to contain number of cubes [0,0,0,0]
	for (int i = 0; i < cityList->size(); i++) {

		if (cityList->at(i)->hasResearchStation()) {
			researchStationCities.append(cityList->at(i)->getName() + ", ");
			mapResearchStation[i] = "[R-S]";
		}
		else
			mapResearchStation[i] = "     ";

		for (int j = 0; j < NUM_OF_DISEASES; j++) {

			if (j == 0)
				temp.append("[");

			temp.append(to_string(cityList->at(i)->getInfectionLevel((InfectType)j) ));

			if (j != NUM_OF_DISEASES - 1)
				temp.append(", ");
			else
				temp.append("]");
		}
		cityInfection[i] = temp;
		temp = "";
	}
}

// Clear Console Screen Function
void MapView::clearScreen() {
	system("cls");
}
