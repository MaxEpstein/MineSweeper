#include <SFML/Graphics.hpp>
#include <string>>
#include <iostream>
#include<fstream>
#include "tile.h"
#include "textures.h"
#include "board.h"

using namespace std;

void setBoard(int& minesLeft,int& columns, int& rows) {
    string columnsHolder;
    string rowsHolder;
    string minesHolder;

    fstream file("boards/config.cfg");
    if (file.is_open()) {
        getline(file, columnsHolder);
        getline(file, rowsHolder);
        getline(file, minesHolder);
    }
    else
        cout << "ERROR FILE NOT OPEN" << endl;

    columns = stoi(columnsHolder);
    rows = stoi(rowsHolder);
    minesLeft = stoi(minesHolder);
}

void setCounter(sf::Sprite& item, int num, textures& a) {
    if (num == 0)
        item.setTexture(a.digits0);
    if (num == 1)
        item.setTexture(a.digits1);
    if (num == 2)
        item.setTexture(a.digits2);
    if (num == 3)
        item.setTexture(a.digits3);
    if (num == 4)
        item.setTexture(a.digits4);
    if (num == 5)
        item.setTexture(a.digits5);
    if (num == 6)
        item.setTexture(a.digits6);
    if (num == 7)
        item.setTexture(a.digits7);
    if (num == 8)
        item.setTexture(a.digits8);
    if (num == 9)
        item.setTexture(a.digits9);
}

int loadTestBoard(string boardName, board& board, textures& textures) {
    string holder;
    vector<string> layout;

    fstream file("boards/" + boardName);
    if (file.is_open()) {
        //cout << "file open " << endl;
        while (getline(file, holder)) {
            layout.push_back(holder);
        }
    }

    int mineCounter = 0;
    for (int y = 0; y < board.rows; y++) {
        for (int x = 0; x < board.columns; x++) {
            if (layout[y].at(x) == *"1") {
                //cout << "x: " << x << " y: " << y << endl;
                board.gameSet[x][y].isMine = true;
                board.gameSet[x][y].isFlag = false;
                board.gameSet[x][y].isUncovered = false;
                board.gameSet[x][y].show.setTexture(textures.hidden);
                mineCounter++;
            }
            else if (layout[y].at(x) == *"0") {
                board.gameSet[x][y].isUncovered = false;
                board.gameSet[x][y].isFlag = false;
                board.gameSet[x][y].isMine = false;
                board.gameSet[x][y].show.setTexture(textures.hidden);
            }
            else
                cout << "ERROR" << endl;
           
        }
    }//end of both for loops
    //cout << "mines: " << mineCounter << endl;
    board.nonMine = board.rows * board.columns - mineCounter;
    return mineCounter;
}

int main()
{
    int minesLeft = 0;
    int columns = 0;
    int rows = 0;
    bool gameOver = false;
    bool debugB = false;
    setBoard(minesLeft, columns, rows);

    sf::RenderWindow window(sf::VideoMode((columns * 32), (rows * 32) + 88), "MineSweeper");
    
    //cout << "Mines left: " << minesLeft << endl;
    //cout << "columns: " << columns << endl;
    //cout << "rows: " << rows << endl;
    textures texture;
    board gameBoard(columns, rows, minesLeft);
    gameBoard.populateBoard();
    gameBoard.remakeBoard(gameOver);

    sf::Sprite face;
    sf::Sprite debug;
    sf::Sprite testBoard1;
    sf::Sprite testBoard2;
    sf::Sprite testBoard3;
    sf::Sprite counterLeft;
    sf::Sprite counterMiddle;
    sf::Sprite counterRight;
    sf::Sprite negative;

    debug.setTexture(texture.debug);
    testBoard1.setTexture(texture.test1);
    testBoard2.setTexture(texture.test2);
    testBoard3.setTexture(texture.test3);
    face.setTexture(texture.happyFace);
    negative.setTexture(texture.digitsNeg);

    testBoard3.setPosition(20 * 32, rows * 32);
    testBoard2.setPosition(18 * 32, rows * 32);
    testBoard1.setPosition(16 * 32, rows * 32);
    debug.setPosition(14 * 32, rows * 32);
    face.setPosition(10 * 32, rows * 32);
    negative.setPosition(0, rows * 32);
    counterLeft.setPosition(21, rows * 32);
    counterMiddle.setPosition(42, rows * 32);
    counterRight.setPosition(63, rows * 32);

    int holder = minesLeft;
    int firstDigit;
    int secondDigit;
    int thirdDigit;
    int originalMines = minesLeft;

    while (window.isOpen())
    {
        holder = abs(minesLeft);
        sf::Vector2f Mouse = (sf::Vector2f)(sf::Mouse::getPosition(window));
        sf::Vector2f MouseCopy = Mouse;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                Mouse /= 32.0f;
                Mouse.x = floor(Mouse.x);
                Mouse.y = floor(Mouse.y);
               // cout << "mouse pressed at x: " << Mouse.x << " Y: " << Mouse.y << endl;
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (Mouse.x < columns && Mouse.y < rows) {
                        if (!gameBoard.gameSet[Mouse.x][Mouse.y].isFlag && !gameBoard.gameSet[Mouse.x][Mouse.y].isUncovered) {
                            int num = gameBoard.tileClicked(Mouse.x, Mouse.y, true, gameOver);
                            if (num == 1)
                                face.setTexture(texture.loseFace);
                        }
                    }
                    else if (debug.getGlobalBounds().contains(MouseCopy)) {
                        if (debugB == false) {
                            gameBoard.showAllMines(gameOver);
                            debugB = true;
                        }
                        else if (debugB == true) {
                            gameBoard.hideAllMines(gameOver);
                            debugB = false;
                        }
                            
                    }
                    else if (face.getGlobalBounds().contains(MouseCopy)) {
                        gameBoard.remakeBoard(gameOver);
                        minesLeft = originalMines;
                        face.setTexture(texture.happyFace);
                    }

                    else if (testBoard1.getGlobalBounds().contains(MouseCopy)) {
                        minesLeft = loadTestBoard("testBoard1.brd", gameBoard, texture);
                        gameOver = false;
                        face.setTexture(texture.happyFace);
                        //LOAD BOARD1
                    }
                    else if (testBoard2.getGlobalBounds().contains(MouseCopy)) {
                        minesLeft = loadTestBoard("testBoard2.brd", gameBoard, texture);
                        gameOver = false;
                        face.setTexture(texture.happyFace);
                        //LOAD BOARD2
                    }
                    else if (testBoard3.getGlobalBounds().contains(MouseCopy)) {
                        minesLeft = loadTestBoard("testBoard3.brd", gameBoard, texture);
                        gameOver = false;
                        face.setTexture(texture.happyFace);
                        //LOAD BOARD3
                    }

                    if (gameBoard.nonMine == 0) {
                        gameOver = true;
                        face.setTexture(texture.winFace);
                        gameBoard.flagAllMines();
                        minesLeft = 0;
                    }
                }
                
                if (event.mouseButton.button == sf::Mouse::Right) {
                    if (Mouse.x < columns && Mouse.y < rows && !gameOver) {
                        if ((!gameBoard.gameSet[Mouse.x][Mouse.y].isFlag) && (!gameBoard.gameSet[Mouse.x][Mouse.y].isUncovered)) {
                            gameBoard.gameSet[Mouse.x][Mouse.y].isFlag = true;
                            minesLeft--;
                        }
                            
                        else if (gameBoard.gameSet[Mouse.x][Mouse.y].isFlag)
                        {
                            gameBoard.gameSet[Mouse.x][Mouse.y].isFlag = false;
                            minesLeft++;
                        }
                            
                    }
                }
            }
            
        }

        firstDigit = holder % 10;
        holder /= 10;
        secondDigit = holder % 10;
        holder /= 10;

        if (holder > 0) {
            thirdDigit = holder % 10;
            holder /= 10;
        }

        else
            thirdDigit = 0;

        setCounter(counterMiddle, secondDigit, texture);
        setCounter(counterRight, firstDigit, texture);
        setCounter(counterLeft, thirdDigit, texture);


        window.clear(sf::Color::White);
        window.draw(testBoard1);
        window.draw(testBoard2);
        window.draw(testBoard3);
        if (minesLeft < 0)
            window.draw(negative);
        window.draw(counterLeft);
        window.draw(counterMiddle);
        window.draw(counterRight);
        window.draw(face);
        window.draw(debug);
        gameBoard.drawBoard(window);
        window.display();
    }

    return 0;
}