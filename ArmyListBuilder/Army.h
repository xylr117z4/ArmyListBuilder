#ifndef ARMY_H
#define ARMY_H

#include <json.hpp>
#include <fstream>
#include <sstream>

#include "Squad.h"

namespace js = nlohmann; //shorten namespace

class Army
{
public:
	Army();
	Army(std::string name, int race);
	void writeToFile();
	void readFromFile(std::string str);
	void addNewSquad(int id, int race);
	~Army();
	int armyRace;
	int armyPalette;
	std::string armyName;
	int numberOfSquads;
	std::vector<Squad> squads;

};

#endif // ARMY_H
