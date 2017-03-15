
#include "MapView.h"
#include "CommonLibrary.h"

using namespace std;


// Constructor
MapView::MapView() {
	
}

// Destructor
MapView::~MapView() { }

// ============ Print Map Function ====================
void MapView::printMap(Markers* marker) {

	cout << "\n ======================================================================================================================================================================================================================= " << endl;
	cout << "                                                                                                          PANDEMIC MAP " << endl;
	cout << "                                                                                                      ---------------------              " << endl;
	cout << "                                                                                          Legend: Infection Cubes [Yellow, Red, Blue, Black]  " << endl;
	cout << "                                                                                                         ============== \n" << endl;
	// Printing Map
	cout << "                                                                        London          Essen       St. Pertersberg                    Moscow                                           Beijing         Seoul        " << endl;
	cout << "                                                           --------- " << cityInfection[12] << " -- " << cityInfection[21] << " -- " << cityInfection[32] << " ----------------- " << cityInfection[41] << "                                     " << cityInfection[35] << " -- " << cityInfection[23] <<  endl;
	cout << "                                                          |                       \\               \\                       |               |                                                       /                 " << endl;
	cout << "                                                          |                |       \\      |        \\                      |               |                                               |      /        |          " << endl;
	cout << "                                                          |                |        \\     |         \\                     |               |                                               |     /         |           " << endl;
	cout << "     San Fransisco     Chicago         Montreal        New York         Madrid           Paris          Milan             |               |                                            Shanghai         Tokyo        " << endl;
	cout << " ----" << cityInfection[8] << " -- " << cityInfection[3] << " -- " << cityInfection[7] << " -- " << cityInfection[6] << " -- " << cityInfection[13] << " -- " << cityInfection[20] << " -- " << cityInfection[31] << "         |               |                                          " << cityInfection[36] << " -- " << cityInfection[14] << "----" << endl;
	cout << "    /               /            \\              \\                                 \\       |                      \\        |               |                                                  \\                       " << endl;
	cout << "   /      |       /        |       \\              \\       |                |       \\      |                       \\       |               |                                               |   \\           |               " << endl;
	cout << "  /       |     /          |         \\              \\     |                |        \\     |                        \\      |               |                                               |    \\          |             " << endl;
	cout << "     Los Angeles           |            Atlanta       Washington           |            Algiers                        Istanbul         Tehran                                            |     \\       Osaka        " << endl;
	cout << "     " << cityInfection[9] << "          |         " << cityInfection[0] << " -- " << cityInfection[2] << "          |         " << cityInfection[22] << " -----------------  " << cityInfection[34] << "    " << cityInfection[46] << " --------                                |      \\   " << cityInfection[24] << endl;
	cout << "    /                      |                    \\                          |                                      /                /                      |                               |       \\                  " << endl;
	cout << "   /      |                |                      \\       |                |              |                     /         |      /        |               |                               |        \\      |            " << endl;
	cout << "  /       |                |                        \\     |                |              |                   /           |    /          |               |                               |         \\     |            " << endl;
	cout << "          |           Mexico City                       Miami              |              |             Cairo          Baghdad         Karachi          Delhi           Kokata        Hong Kong         Taipei     " << endl;
	cout << "           --------- " << cityInfection[5] << " ------------------ " << cityInfection[1] << "          |              ---------- " << cityInfection[33] << " -- " << cityInfection[42] << " -- " << cityInfection[47] << " -- " << cityInfection[44] << " -- " << cityInfection[38] << " -- " << cityInfection[27] << " -- " << cityInfection[25] << endl;
	cout << "                                 \\                                         |                                   \\                   /               /                /               /            \\                      " << endl;
	cout << "                           |       --------------         |                |                              |       \\       |      /        |      /         |      /        |      /       |        \\      |        /  " << endl;
	cout << "                           |                     \\        |                |                              |         \\     |    /          |    /           |    /          |    /         |          \\    |       /    " << endl;
	cout << "                         Lima                      \\    Bogota        Sao Paula          Lagos         Khartoum         Riyadh          Mumbai          Chennai         Bangkok    Ho Chi Minh City     Manila   /  " << endl;
	cout << "                     " << cityInfection[10] << " ------------------ " << cityInfection[4] << " -- " << cityInfection[11] << " -- " << cityInfection[18] << " -- " << cityInfection[29] << "    " << cityInfection[42] << "    " << cityInfection[45] << " -- " << cityInfection[39] << " -- " << cityInfection[37] << " -- " << cityInfection[26] << " -- " << cityInfection[15] << endl;
	cout << "                                                                                                    /                                                                              /                                  " << endl;
	cout << "                           |                              |                |               |      /       |                                                |               |      /                       |         /     " << endl;
	cout << "                           |                              |                |               |    /         |                                                |               |     /                        |        /   " << endl;
	cout << "                       Santiago                      Buenos Aires          |           Kinshasa      Johannesburg                                          |            Jakarta                         Sydney    /        " << endl;
	cout << "                     " << cityInfection[17] << "                    " << cityInfection[19] << " ---------          " << cityInfection[30] << " -- " << cityInfection[40] << "                                          --------- " << cityInfection[28] << " ------------------ " << cityInfection[16] << endl;
	cout << endl;

	// Printing Marker Status
	cout << "\n             ------------------------------------------------------------------------------------------------ MARKERS -----------------------------------------------------------------------------  " << endl;
	cout << "                                                 Disease Status    Yellow Disease: " << cureStatusEnumToString(marker->getCureMarker((InfectType)0)) << "  |    Cubes Left    Yellow: " << fillNumber(marker->getNumOfDiseaseCubes((InfectType) 0)) << "  |            Infection Outbreak: " << marker->getOutbreakCounter() << endl;
	cout << "                                                ----------------      Red Disease: " << cureStatusEnumToString(marker->getCureMarker((InfectType)1)) << "  |   ------------      Red: " << fillNumber(marker->getNumOfDiseaseCubes((InfectType) 1)) << "  |               Infecttion Rate: " << marker->getInfectionRate() << endl;
	cout << "                                                                     Blue Disease: " << cureStatusEnumToString(marker->getCureMarker((InfectType)2)) << "  |                    Blue: " << fillNumber(marker->getNumOfDiseaseCubes((InfectType) 2)) << "  |    Research Station Remaining: " << marker->getNumOfResearchStations() <<endl;
	cout << "                                                                    Black Disease: " << cureStatusEnumToString(marker->getCureMarker((InfectType)3)) << "  |                   Black: " << fillNumber(marker->getNumOfDiseaseCubes((InfectType) 3)) << "  |    Research Station Locations: " << researchStationCities <<  endl;
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

		if (cityList->at(i)->hasResearchStation())
			researchStationCities.append(cityList->at(i)->getName() + ", ");

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
