#include "board.h"
#include <random>
board::board(int column, int row, int mine) {
	columns = column;
	rows = row;
	mines = mine;
	nonMine = (columns * rows) - mines;
}
void board::populateBoard() {

	vector<tile> eachRow(rows);
	for (int y = 0; y < eachRow.size(); y++) {
		eachRow[y].show.setTexture(a.hidden);
		eachRow[y].flagS.setTexture(a.flag);
	}

	for (int i = 0; i < columns; i++) {
		gameSet.push_back(eachRow);
		for (int w = 0; w < rows; w++) {

			gameSet[i][w].show.setPosition((i * 32), (w * 32));
			gameSet[i][w].flagS.setPosition((i * 32), (w * 32));
			gameSet[i][w].numberS.setPosition((i * 32), (w * 32));
		}
	}
	
}

void board::remakeBoard(bool& gameOver) {
	gameOver = false;
	nonMine = (columns * rows) - mines;
	random_device rand;

	int totalMines = 0;
	vector<int> xs(mines);
	vector<int> ys(mines);

	for (int u = 0; u < mines; u++) {
		int p = rand() % (columns);
		int q = rand() % (rows);
		xs[u] = p;
		ys[u] = q;
		for (int o = 0; o < u; o++) {
			if (p == xs[o] && q == ys[o]) {
				u--;
			}
		}
	}

	for (int x = 0; x < columns; x++) {
		for (int y = 0; y < rows; y++) {
			gameSet[x][y].isUncovered = false;
			gameSet[x][y].show.setTexture(a.hidden);
			gameSet[x][y].isMine = false;
			gameSet[x][y].isFlag = false;
		}
	}

	int n, m;
	for (int x = 0; x < mines; x++) {
		gameSet[xs[x]][ys[x]].isMine = true;
	}

}

void board::showAllMines(bool gameOver) {
	if (!gameOver) {
		for (int x = 0; x < columns; x++) {
			for (int y = 0; y < rows; y++) {
				if (gameSet[x][y].isMine) {
					gameSet[x][y].numberS.setTexture(a.mine);
					gameSet[x][y].isUncovered = true;
				}
			}
		}
	}
}

void board::flagAllMines() {
	for (int x = 0; x < columns; x++) {
		for (int y = 0; y < rows; y++) {
			if (gameSet[x][y].isMine) {
				gameSet[x][y].isFlag = true;
			}
		}
	}
}

void board::hideAllMines(bool gameOver) {
	if (!gameOver) {
		for (int x = 0; x < columns; x++) {
			for (int y = 0; y < rows; y++) {
				if (gameSet[x][y].isMine) {
					gameSet[x][y].numberS.setTexture(a.hidden);
					gameSet[x][y].isUncovered = false;
				}
			}
		}
	}
}

void board::drawBoard(sf::RenderWindow& window) {
	for (int x = 0; x < columns; x++) {
		for (int i = 0; i < rows; i++) {
			window.draw(gameSet[x][i].show);
			if (gameSet[x][i].isFlag) {
				window.draw(gameSet[x][i].flagS);
			}
			if (gameSet[x][i].isUncovered) {
				window.draw(gameSet[x][i].numberS);
			}
		}
	}
}

int board::tileClicked(int x, int y, bool first, bool& gameOver) {
	if (gameSet[x][y].isMine && first) {
		showAllMines(gameOver);
		gameOver = true;
		return 1;
	}
	else if (!gameSet[x][y].isUncovered && !gameSet[x][y].isFlag && !gameOver){
		nonMine--;
		//cout << "Non Mine: " << nonMine << endl;
		gameSet[x][y].isUncovered = true;
		int around = minesAround(x, y);
		gameSet[x][y].setNumber(around, a);
		if (around == 0) {
			if (x == 0 && y == 0) {
				tileClicked(x + 1, y, false, gameOver);
				tileClicked(x + 1, y + 1, false, gameOver);
				tileClicked(x, y + 1, false, gameOver);
			}
			else if (x == 0 && y == (rows - 1)) {
				tileClicked(x + 1, y, false, gameOver);
				tileClicked(x + 1, y - 1, false, gameOver);
				tileClicked(x, y - 1, false, gameOver);
			}
			else if (x == (columns - 1) && y == (rows - 1)) {
				tileClicked(x - 1, y, false, gameOver);
				tileClicked(x - 1, y - 1, false, gameOver);
				tileClicked(x, y - 1, false, gameOver);
			}
			else if (x == (columns - 1) && y == 0) {
				tileClicked(x - 1, y, false, gameOver);
				tileClicked(x - 1, y + 1, false, gameOver);
				tileClicked(x, y + 1, false, gameOver);
			}
			else if (x == 0) {
				tileClicked(x + 1, y, false, gameOver);
				tileClicked(x + 1, y + 1, false, gameOver);
				tileClicked(x, y + 1, false, gameOver);
				tileClicked(x, y - 1, false, gameOver);
				tileClicked(x + 1, y - 1, false, gameOver);
			}
			else if (y == 0) {
				tileClicked(x + 1, y, false, gameOver);
				tileClicked(x + 1, y + 1, false, gameOver);
				tileClicked(x, y + 1, false, gameOver);
				tileClicked(x - 1, y, false, gameOver);
				tileClicked(x - 1, y + 1, false, gameOver);
			}
			else if (y == rows-1) {
				tileClicked(x + 1, y, false, gameOver);
				tileClicked(x + 1, y - 1, false, gameOver);
				tileClicked(x, y - 1, false, gameOver);
				tileClicked(x - 1, y, false, gameOver);
				tileClicked(x - 1, y - 1, false, gameOver);
			}
			else if (x == columns-1) {
				tileClicked(x - 1, y, false, gameOver);
				tileClicked(x - 1, y - 1, false, gameOver);
				tileClicked(x, y - 1, false, gameOver);
				tileClicked(x, y + 1, false, gameOver);
				tileClicked(x - 1, y + 1, false, gameOver);
			}
			else {
				tileClicked(x + 1, y + 1, false, gameOver);
				tileClicked(x + 1, y, false, gameOver);
				tileClicked(x + 1, y - 1, false, gameOver);
				tileClicked(x - 1, y + 1, false, gameOver);
				tileClicked(x - 1, y, false, gameOver);
				tileClicked(x - 1, y - 1, false, gameOver);
				tileClicked(x, y - 1, false, gameOver);
				tileClicked(x, y + 1, false, gameOver);
			}
		}
		return 2;
	}
}

int board::minesAround(int x, int y) {
	int mines = 0;
	if (x == 0 && y == 0) {
		if (gameSet[x + 1][y].isMine)
			mines++;
		if (gameSet[x + 1][y + 1].isMine)
			mines++;
		if (gameSet[x][y + 1].isMine)
			mines++;
	}

	else if (x == 0 && y == (rows - 1)) {
		if (gameSet[x + 1][y].isMine)
			mines++;
		if (gameSet[x + 1][y - 1].isMine)
			mines++;
		if (gameSet[x][y - 1].isMine)
			mines++;
	}

	else if (x == (columns-1) && y == (rows - 1)) {
		if (gameSet[x - 1][y].isMine)
			mines++;
		if (gameSet[x - 1][y - 1].isMine)
			mines++;
		if (gameSet[x][y - 1].isMine)
			mines++;
	}

	else if (x == (columns - 1) && y == 0) {
		if (gameSet[x - 1][y].isMine)
			mines++;
		if (gameSet[x - 1][y + 1].isMine)
			mines++;
		if (gameSet[x][y + 1].isMine)
			mines++;
	}

	else if (x == 0) {
		if (gameSet[x + 1][y].isMine)
			mines++;
		if (gameSet[x + 1][y + 1].isMine)
			mines++;
		if (gameSet[x][y + 1].isMine)
			mines++;
		if (gameSet[x][y - 1].isMine)
			mines++;
		if (gameSet[x + 1][y - 1].isMine)
			mines++;
	}

	else if (y == 0) {
		if (gameSet[x + 1][y].isMine)
			mines++;
		if (gameSet[x + 1][y + 1].isMine)
			mines++;
		if (gameSet[x][y + 1].isMine)
			mines++;
		if (gameSet[x - 1][y].isMine)
			mines++;
		if (gameSet[x - 1][y + 1].isMine)
			mines++;
	}

	else if (y == rows - 1) {
		if (gameSet[x + 1][y].isMine)
			mines++;
		if (gameSet[x + 1][y - 1].isMine)
			mines++;
		if (gameSet[x][y - 1].isMine)
			mines++;
		if (gameSet[x - 1][y].isMine)
			mines++;
		if (gameSet[x - 1][y - 1].isMine)
			mines++;
	}

	else if (x == columns - 1) {
		if (gameSet[x - 1][y].isMine)
			mines++;
		if (gameSet[x - 1][y - 1].isMine)
			mines++;
		if (gameSet[x][y - 1].isMine)
			mines++;
		if (gameSet[x][y+1].isMine)
			mines++;
		if (gameSet[x - 1][y + 1].isMine)
			mines++;
	}
	else {
		if (gameSet[x - 1][y].isMine)
			mines++;
		if (gameSet[x - 1][y - 1].isMine)
			mines++;
		if (gameSet[x][y - 1].isMine)
			mines++;
		if (gameSet[x - 1][y + 1].isMine)
			mines++;
		if (gameSet[x][y + 1].isMine)
			mines++;
		if (gameSet[x+1][y + 1].isMine)
			mines++;
		if (gameSet[x+1][y - 1].isMine)
			mines++;
		if (gameSet[x+1][y].isMine)
			mines++;
	}

	return mines;
}


