#pragma once

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

//GAME RULE CONSTANTS/////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
const int NUM_OF_DISEASES = 4;
const int NUM_OF_DISEASE_CUBES_PER_TYPE = 24;
const int MAX_CUBES_PER_CITY = 3;
const int MAX_OUTBREAKES = 8;
const int INFECTION_RATE[] = { 2,2,2,3,3,4,4 };

const int NUM_OF_PLAYERS = 2;
const int NUM_OF_STARTING_CARDS_PER_PLAYER = 4;
const int MAX_HAND_SIZE = 7;

const int NUM_OF_CITIES = 48;
const int NUM_OF_RESEARCH_STATIONS = 6;

//ENUMS///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
enum InfectType : int{
	yellow = 0,
	red = 1,
	blue = 2,
	black = 3
};

string enumToString(InfectType t);