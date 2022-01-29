#pragma once
#include "textures.h"
#include <vector>

class tile
{
public:
	tile();
	int numberOfMines;
	bool isUncovered;
	bool isFlag;
	bool isMine;
	sf::Texture numberMine;
	sf::Texture flag;
	sf::Texture revelaed;
	sf::Texture hidden;

	sf::Sprite show;
	sf::Sprite flagS;
	sf::Sprite numberS;


	void setText(sf::Texture& set);
	void setNumber(int num, textures& a);
};

