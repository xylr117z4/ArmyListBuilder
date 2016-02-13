#include "Army.h"

Army::Army(){
}

Army::Army(std::string name, int id){
	armyName = name;
	armyID = id;
	armyPalette = 0;
	numberOfSquads = 1;
}

void Army::writeToFile(){
	js::json armyOutput;
	std::ofstream armyOutputFile;
	std::stringstream ss;
	
	armyOutput["Name"] = armyName;
	armyOutput["Army"] = armyID;
	armyOutput["Palette"] = armyPalette;
	armyOutput["Squads"]["Number"] = numberOfSquads;
	for(int i = 0; i < numberOfSquads; ++i){
		ss.str("");
		ss << i;
		armyOutput["Squads"][ss.str()]["Stats"] = 0; //squads[i].stats
		
		//testing what the squad will store just a json thing and put it in gear
		js::json thing;
		thing["stuff"] = 9001;
		armyOutput["Squads"][ss.str()]["Gear"] = thing; //squads[i].gear
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
	armyID = armyInput["Army"];
	armyPalette = armyInput["Palette"];
	numberOfSquads = armyInput["Squads"]["Number"];
	
	for(int i = 0; i < numberOfSquads; ++i){
		ss.str("");
		ss << i;
		//armyInput["Squads"][ss.str()]["Stats"] = 0; //squads[i].stats
		
		//testing what the squad will store just a json thing and put it in gear
		js::json thing;
		thing["stuff"] = 9001;
		thing = armyInput["Squads"][ss.str()]["Gear"]; //squads[i].gear
	}
}

Army::~Army(){
}