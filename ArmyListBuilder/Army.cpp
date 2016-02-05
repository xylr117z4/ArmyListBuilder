#include "Army.h"

Army::Army(){
}

Army::Army(std::string name, int id){
	armyName = name;
	armyID = id;
	numberOfSquads = 2;
}

void Army::writeToFile(){
	js::json armyOutput;
	std::ofstream armyOutputFile;
	std::stringstream ss;
	
	armyOutput["Name"] = armyName;
	armyOutput["Army"] = armyID;
	armyOutput["Squads"]["Number"] = numberOfSquads;
	for(int i = 0; i < numberOfSquads; ++i){
		ss.str("");
		ss << i;
		armyOutput["Squads"][ss.str()]["Stats"] = 0; //squads[i].stats
		armyOutput["Squads"][ss.str()]["Gear"] = 0; //squads[i].gear
	}
	
	armyOutputFile.open(armyName + ".json");
	armyOutputFile << armyOutput;
	armyOutputFile.close();
}

Army::~Army(){
}

