#ifndef ARMY_H
#define ARMY_H

#include <json.hpp>
#include <fstream>
#include <sstream>

namespace js = nlohmann; //shorten namespace

class Army
{
public:
	Army();
	Army(std::string name, int id);
	void writeToFile();
	~Army();
	int armyID;
	int armyPalette;
	std::string armyName;
	int numberOfSquads;

};

#endif // ARMY_H
