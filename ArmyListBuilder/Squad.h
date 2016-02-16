#ifndef SQUAD_H
#define SQUAD_H

#include <vector>

class Squad{
	public:
		Squad(int id, int race); //squad number in army, race
		~Squad();
		
		int squadId;
		int squadRace;
		int numberOfMembers;
		int baseSkill;
		int speed;
		int armor;
		int health;
		int stuff;
		int squadType;
		int squadRole;
		std::vector<int> members;
		int points;
	

};

#endif // SQUAD_H
