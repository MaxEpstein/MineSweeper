#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class textures
{
public:
	textures();

	sf::Texture hidden;
	sf::Texture revealed;

	sf::Texture num1;
	sf::Texture num2;
	sf::Texture num3;
	sf::Texture num4;
	sf::Texture num5;
	sf::Texture num6;
	sf::Texture num7;
	sf::Texture num8;
	sf::Texture mine;

	sf::Texture test1;
	sf::Texture test2;
	sf::Texture test3;

	sf::Texture happyFace;
	sf::Texture loseFace;
	sf::Texture winFace;

	sf::Texture debug;

	sf::Texture digits1;
	sf::Texture digits2;
	sf::Texture digits3;
	sf::Texture digits4;
	sf::Texture digits5;
	sf::Texture digits6;
	sf::Texture digits7;
	sf::Texture digits8;
	sf::Texture digits9;
	sf::Texture digits0;
	sf::Texture digitsNeg;

	sf::Texture flag;
};

