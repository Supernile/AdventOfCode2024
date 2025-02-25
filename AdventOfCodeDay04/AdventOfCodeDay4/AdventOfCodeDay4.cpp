// AdventOfCodeDay4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#define SIZE 140

void generateCrossword(string FILEPATH, int arrayWidth, int arrayHeight, char crossword[][SIZE] ) {
    string line;
    ifstream crosswordFile(FILEPATH);

    int row = 0;
    while (getline(crosswordFile, line) && row < arrayHeight) {
        for (int col = 0; col < arrayHeight; col++) {
            crossword[row][col] = line[col];
        }
        row++;
    }
    crosswordFile.close();
}

int findNumberOfWordsXMAS(char crossword[][SIZE], int arrayWidth, int arrayHeight, string targetString) {
    bool checkUp = true;
    bool checkDown = true;
    bool checkLeft = true;
    bool checkRight = true;

    bool wordFound = false;

    int numberOfWords = 0;
    int maxIndex = targetString.length() - 1;

    for (int row = 0; row < arrayHeight; row++) {
        for (int col = 0; col < arrayWidth; col++){
            checkUp = true;
            checkDown = true;
            checkLeft = true;
            checkRight = true;

            if (crossword[row][col] == 'X') {
                /*for (int i = -1; i < 2; i++) {
                    for (int j = -1; j < 2; j++) {
                        wordFound = true;
                        for (int k = 1; k < targetString.length(); k++) {
                            if (((row + (k*i) < 0 || col + (k*j) < 0) || (row + (k * i) > maxIndex || col + (k * j) < maxIndex)) && crossword[row + (k * i)][col + (k * j)] != targetString[k]) {
                                wordFound = false;
                            }
                        }
                    }
                }*/


                //Check that up down left and right have at least three spaces (else XMAS will never fit and it's not worth checking that direction)
                //up
                int num = row - (targetString.length() - 1);
                if (num < 0) {
                    checkUp = false;
                }
                //Down
                if (row + (targetString.length() - 1) > (arrayHeight - 1)) {
                    checkDown = false;
                }
                // Left
                num = col - (targetString.length() - 1);
                if (num < 0) {
                    checkLeft = false;
                }
                // Right
                if (col + (targetString.length() - 1) > (arrayWidth - 1)) {
                    checkRight = false;
                }

                //Check for words in each direction
                //Diagonal Up and Left
                if (checkUp && checkLeft) {
                    wordFound = true;
                    for (int i = 1; i < targetString.length(); i++) {
                        if (crossword[row - i][col - i] != targetString[i]) {
                            wordFound = false;
                        }
                    }
                    if (wordFound == true) {
                        numberOfWords++;
                    }
                }
                // Vertically Up
                if (checkUp) {
                    wordFound = true;
                    for (int i = 1; i < targetString.length(); i++) {
                        if (crossword[row - i][col] != targetString[i]) {
                            wordFound = false;
                        }
                    }
                    if (wordFound == true) {
                        numberOfWords++;
                    }
                }
                // Diagonally Up and Right
                if (checkUp && checkRight) {
                    wordFound = true;
                    for (int i = 1; i < targetString.length(); i++) {
                        if (crossword[row - i][col + i] != targetString[i]) {
                            wordFound = false;
                        }
                    }
                    if (wordFound == true) {
                        numberOfWords++;
                    }
                }
                // Right
                if (checkRight) {
                    wordFound = true;
                    for (int i = 1; i < targetString.length(); i++) {
                        if (crossword[row][col + i] != targetString[i]) {
                            wordFound = false;
                        }
                    }
                    if (wordFound == true) {
                        numberOfWords++;
                    }
                }
                // Diagonally Down and Right
                if (checkDown && checkRight) {
                    wordFound = true;
                    for (int i = 1; i < targetString.length(); i++) {
                        if (crossword[row + i][col + i] != targetString[i]) {
                            wordFound = false;
                        }
                    }
                    if (wordFound == true) {
                        numberOfWords++;
                    }
                }
                // Vertically Down
                if (checkDown) {
                    wordFound = true;
                    for (int i = 1; i < targetString.length(); i++) {
                        if (crossword[row + i][col] != targetString[i]) {
                            wordFound = false;
                        }
                    }
                    if (wordFound == true) {
                        numberOfWords++;
                    }
                }
                // Diagonally Down and Left
                if (checkDown && checkLeft) {
                    wordFound = true;
                    for (int i = 1; i < targetString.length(); i++) {
                        if (crossword[row + i][col - i] != targetString[i]) {
                            wordFound = false;
                        }
                    }
                    if (wordFound == true) {
                        numberOfWords++;
                    }
                }
                // Left
                if (checkLeft) {
                    wordFound = true;
                    for (int i = 1; i < targetString.length(); i++) {
                        if (crossword[row][col - i] != targetString[i]) {
                            wordFound = false;
                        }
                    }
                    if (wordFound == true) {
                        numberOfWords++;
                    }
                }
            }
        }
    }
    return numberOfWords;
}

int findNumberOfXMAS(char crossword[][SIZE], int arrayWidth, int arrayHeight, string targetString) {
    bool oneMASFound = false;

    int numberOfMAS = 0;

    // Checks each A in the Array (Doesn't check edges)
    for (int row = 1; row < arrayHeight - 1; row++) {
        for (int col = 1; col < arrayWidth - 1; col++) {
            if (crossword[row][col] == 'A') {
                oneMASFound = false;
                // For statements to iterate between the four elements on the diagonals
                for (int i = -1; i < 3; i += 2) {
                    for (int j = -1; j < 3; j += 2) {
                        char character1 = crossword[i][j];
                        if (crossword[row + i][col + j] == 'M') {
                            if (crossword[row - i][col - j] == 'S') {
                                if (oneMASFound == false) {
                                    oneMASFound = true;
                                }
                                else {
                                    numberOfMAS += 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return numberOfMAS;
}

int main() {
    const string FILEPATH = "text.txt";
    const int arrayHeight = SIZE;
    const int arrayWidth = SIZE;
    string targetString = "XMAS";
    char crossword[arrayHeight][arrayWidth];

    generateCrossword(FILEPATH, arrayWidth, arrayHeight, crossword);
    int numberOfWords = findNumberOfWordsXMAS(crossword, arrayWidth, arrayHeight, targetString);
    int numberOfXMAS = findNumberOfXMAS(crossword, arrayWidth, arrayHeight, targetString);

    std::cout << "The number of instances of \"" + targetString + "\" in the crossword file is ";
    std::cout << numberOfWords;
    std::cout << "\n";

    std::cout << "The number of instances of Mas's in the shape of an X in the crossword file is ";
    std::cout << numberOfXMAS;
    std::cout << "\n";

    //Memory cleanup
    /*for (int row = 0; row < arrayWidth; row++) {
        delete[] crossword[row];
    }
    delete[] crossword;*/

    return 0;
}