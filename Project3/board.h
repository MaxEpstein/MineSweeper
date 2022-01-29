#pragma once
#include "tile.h"
#include "textures.h"
class board
{
public:
	int columns;
	int rows;
	int mines;
	int nonMine;
	textures a;
	vector<vector<tile>> gameSet;
	
	board(int column, int row, int mine);
	void populateBoard();
	void drawBoard(sf::RenderWindow& window);
	int tileClicked(int x, int y, bool yes, bool& gameOver);
	void showAllMines(bool gameOver);
	void remakeBoard(bool& gameOver);
	void hideAllMines(bool gameOver);
	void flagAllMines();
	int minesAround(int x, int y);
};

