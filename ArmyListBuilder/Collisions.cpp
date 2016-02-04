#include "Collisions.h"

namespace col{
	bool AABB(int X1, int Y1, int X2, int Y2, int mouseX, int mouseY){ //button position, button size, mouse position
		if(mouseX >= X1 && mouseY >= Y1 && mouseX <= X1+X2 && mouseY <= Y1+Y2){
			return true;
		}
		return false;
	}
};