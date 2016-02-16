#include "Army.h"

Army::Army(){
}

Army::Army(std::string name, int race){
	armyName = name;
	armyRace = race;
	armyPalette = 0;
	numberOfSquads = 0;
}

void Army::addNewSquad(int id, int race){
	squads.emplace_back(id, race);
	++numberOfSquads;
	printf("numberOfSquads: %d\n\n", squads.size());
}

void Army::writeToFile(){
	js::json armyOutput;
	std::ofstream armyOutputFile;
	std::stringstream ss;
	
	armyOutput["Name"] = armyName;
	armyOutput["Race"] = armyRace;
	armyOutput["Palette"] = armyPalette;
	armyOutput["Squads"]["Number"] = squads.size();
	printf("%d\n\n", squads.size());
	for(unsigned int i = 0; i < squads.size(); ++i){
		ss.str("");
		ss << i;
		armyOutput["Squads"][ss.str()]["Type"] = squads[i].squadType;
		armyOutput["Squads"][ss.str()]["Role"] = squads[i].squadRole;
		
	}
	
	armyOutputFile.open("json/" + armyName + ".json");
	armyOutputFile << armyOutput;
	armyOutputFile.close();
}

void Army::readFromFile(std::string str){
	js::json armyInput;
	std::ifstream armyInputFile;
	std::stringstream ss;
	
	armyInputFile.open("json/" + str);
	armyInputFile >> armyInput;
	armyInputFile.close();

	armyName = armyInput["Name"];
	armyRace = armyInput["Race"];
	armyPalette = armyInput["Palette"];
	numberOfSquads = armyInput["Squads"]["Number"];
	
	for(int i = 0; i < numberOfSquads; ++i){
		ss.str("");
		ss << i;
		Squad temp(i, armyRace);
		temp.squadType = armyInput["Squads"][ss.str()]["Type"];
		temp.squadRole = armyInput["Squads"][ss.str()]["Role"];
		squads.push_back(temp);
	}
	printf("army was loaded\n\n");
}

Army::~Army(){
}