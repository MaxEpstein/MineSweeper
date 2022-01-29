#include "tile.h"
tile::tile() {
	isFlag = false;
	isMine = false;
	isUncovered = false;
	numberOfMines = 0;

}

void tile::setText(sf::Texture& set) {
	show.setTexture(set);
}

void tile::setNumber(int number, textures& a) {
	if (number == 1)
		numberS.setTexture(a.num1);
	else if (number == 2)
		numberS.setTexture(a.num2);
	else if (number == 3)
		numberS.setTexture(a.num3);
	else if (number == 4)
		numberS.setTexture(a.num4);
	else if (number == 5)
		numberS.setTexture(a.num5);
	else if (number == 6)
		numberS.setTexture(a.num6);
	else if (number == 7)
		numberS.setTexture(a.num7);
	else if (number == 8)
		numberS.setTexture(a.num8);
	else if (number == 0)
		numberS.setTexture(a.revealed);

	show.setTexture(a.revealed);
}