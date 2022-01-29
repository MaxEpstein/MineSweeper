#include "textures.h"

textures::textures() {
	hidden.loadFromFile("images/tile_hidden.png");
	revealed.loadFromFile("images/tile_revealed.png");
	num1.loadFromFile("images/number_1.png");
	num2.loadFromFile("images/number_2.png");
	num3.loadFromFile("images/number_3.png");
	num4.loadFromFile("images/number_4.png");
	num5.loadFromFile("images/number_5.png");
	num6.loadFromFile("images/number_6.png");
	num7.loadFromFile("images/number_7.png");
	num8.loadFromFile("images/number_8.png");

	test1.loadFromFile("images/test_1.png");
	test2.loadFromFile("images/test_2.png");
	test3.loadFromFile("images/test_3.png");

	happyFace.loadFromFile("images/face_happy.png");
	loseFace.loadFromFile("images/face_lose.png");
	winFace.loadFromFile("images/face_win.png");

	debug.loadFromFile("images/debug.png");

	digits0.loadFromFile("images/digits.png", sf::IntRect(0, 0, 21, 32));
	digits1.loadFromFile("images/digits.png", sf::IntRect(21, 0, 21, 32));
	digits2.loadFromFile("images/digits.png", sf::IntRect(42, 0, 21, 32));
	digits3.loadFromFile("images/digits.png", sf::IntRect(63, 0, 21, 32));
	digits4.loadFromFile("images/digits.png", sf::IntRect(84, 0, 21, 32));
	digits5.loadFromFile("images/digits.png", sf::IntRect(105, 0, 21, 32));
	digits6.loadFromFile("images/digits.png", sf::IntRect(126, 0, 21, 32));
	digits7.loadFromFile("images/digits.png", sf::IntRect(147, 0, 21, 32));
	digits8.loadFromFile("images/digits.png", sf::IntRect(168, 0, 21, 32));
	digits9.loadFromFile("images/digits.png", sf::IntRect(189, 0, 21, 32));
	digitsNeg.loadFromFile("images/digits.png", sf::IntRect(210, 0, 21, 32));

	flag.loadFromFile("images/flag.png");
	mine.loadFromFile("images/mine.png");
}
