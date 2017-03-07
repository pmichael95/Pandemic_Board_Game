#include "CommonLibrary.h"

//ENUMS////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
string enumToString(InfectType t) {
	switch (t) {
	case 0:
		return "Yellow";
	case 1:
		return "Red";
	case 2:
		return "Blue";
	case 3:
		return "Black";
	default:
		return "INVALID ENUM";
	}
}