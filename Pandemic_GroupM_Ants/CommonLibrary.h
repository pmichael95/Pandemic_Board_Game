#pragma once

#include <vector>

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

//GAME RULE CONSTANTS/////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
const int NUM_OF_DISEASES = 4;
const int NUM_OF_DISEASE_CUBES_PER_TYPE = 24;
const int MAX_CUBES_PER_CITY = 3;

const int MAX_OUTBREAKES = 8;
const int INFECTION_RATE[] = { 2,2,2,3,3,4,4 };
const int INITIAL_INFECTION = 3;
const int EPIDEMIC_INFECTION = 3;

const int NUM_OF_PLAYERS = 2;
const int NUM_OF_STARTING_CARDS_PER_PLAYER = 4;
const int MAX_HAND_SIZE = 7;
const int NUM_OF_ACTIONS = 4;

const int NUM_OF_CITIES = 48;
const int NUM_OF_RESEARCH_STATIONS = 6;

const int NUM_OF_EPIDEMIC_CARDS = 6;
const int NUM_OF_PLAYER_CARDS_DRAWN_PER_TURN = 2;

//GAME FILES/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

const string MAP_INITIAL_FILE = "..";
const string INFECTION_CARD_INITIAL_FILE = "..";
const string PLAYER_CARD_INITIAL_FILE = "..";
const string ROLE_CARD_INITIAL_FILE = "..";

//ENUMS///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
enum InfectType : int{
	yellow = 0,
	red = 1,
	blue = 2,
	black = 3
};

string infectTypeEnumToString(InfectType t);

enum CureStatus {
	notCured,
	cured,
	eradicated
};

string cureStatusEnumToString(CureStatus c);