// AdventOfCodeDay8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

const std::vector<std::string> testMap = {
"....h.....Q..............Y........................",
"...............................Y........C.........",
"...............m..........x................B......",
"........................Y..............qB.........",
"......g4.........................h..Y.....q...c...",
"................n.....R...........................",
".......................................w........5.",
"........g...m...........................w5........",
"..n...........R.1................W.......q.5......",
".........h...n.................e..................",
"...............................R..........B....C..",
".........4................................5.e.....",
".......0..4......n.......x..w.....................",
".......g.....m........x..b.....W.....B.......w....",
"..............m........................3......C...",
"........q...0.......h....................C.3......",
"..................3.....................D.........",
"...............R..........3.............X.........",
"..............................W............k2.....",
"..........7............................2..........",
"...............A.............................X...2",
".......................c...x......................",
"....................................d.............",
".....1......................d.....................",
"...........1...........................e..........",
".........0.7K.........................2.........W.",
"...b......0.....A.................................",
"......................1....ic.....................",
"......b......................i....................",
"..Q.....b..........................A..E...........",
"...7.........................V....................",
"........A.....................v......d............",
"........v............c...................8E.......",
"..............................V........8.....E..N.",
"......................6...........................",
".......I....M....................V................",
"...G......................a.......8...............",
".........r.9........a...i..................X......",
"...............r..i...............e............N..",
".....H...........k....9.....6...............8.....",
".v.....................6................V.........",
".........v.......a........k..........D............",
"Ha..........k.........K........E.......d..........",
"...............y.MG..............6....D...........",
".........H..G...M......9.K..............N.........",
".......G.........................K................",
"...............M.........I.......D................",
"..................................................",
"....r....y................9.......................",
"....y................................N............"
};

std::vector<std::string> testMapAntinodes = {
"....h.....Q..............Y........................",
"...............................Y........C.........",
"...............m...........................B......",
"........................Y..............qB.........",
"......g4.........................h..Y.....q...c...",
"................n.....R...........................",
".......................................w........5.",
"........g...m...........................w5........",
"..n...........R.1................W.......q.5......",
".........h...n.................e..................",
"...............................R..........B....C..",
".........4................................5.e.....",
".......0..4......n..........w.....................",
".......g.....m...........b.....W.....B.......w....",
"..............m........................3......C...",
"........q...0.......h....................C.3......",
"..................3.....................D.........",
"...............R..........3.......................",
"..............................W............k2.....",
"..........7............................2..........",
"...............A.................................2",
".......................c..........................",
"....................................d.............",
".....1......................d.....................",
"...........1...........................e..........",
".........0.7K.........................2.........W.",
"...b......0.....A.................................",
"......................1....ic.....................",
"......b......................i....................",
"..Q.....b..........................A..E...........",
"...7.........................V....................",
"........A.....................v......d............",
"........v............c...................8E.......",
"..............................V........8.....E..N.",
"......................6...........................",
".......I....M....................V................",
"...G......................a.......8...............",
".........r.9........a...i.........................",
"...............r..i...............e............N..",
".....H...........k....9.....6...............8.....",
".v.....................6................V.........",
".........v.......a........k..........D............",
"Ha..........k.........K........E.......d..........",
"...............y.MG..............6....D...........",
".........H..G...M......9.K..............N.........",
".......G.........................K................",
"...............M.........I.......D................",
"..................................................",
"....r....y................9.......................",
"....y................................N............"
};

/*const std::vector<std::string> testMap = {
"............",
"........0...",
".....0......",
".......0....",
"....0.......",
"......A.....",
"............",
"............",
"........A...",
".........A..",
"............",
"............"
};

std::vector<std::string> testMapAntinodes = {
"............",
"........0...",
".....0......",
".......0....",
"....0.......",
"......A.....",
"............",
"............",
"........A...",
".........A..",
"............",
"............"
};*/


bool IsPrevouslyChecked(int i, int j, std::string prevouslyCheckedFrequencies) {
    for (int k = 0; k < prevouslyCheckedFrequencies.length(); k++) {
        if (k == testMap[i][j]) {
            return false;
        }
    }
    return true;
}

int Part1() {
    int value = 0;

    std::string mapStrip;
    std::string previouslyCheckedFrequencies;
    char targetChar;
    int antennaDistanceX;
    int antennaDistanceY;
    int whileLoopIncrement;

    //Simple code to traverse the array
    for (int row = 0; row < testMap.size(); row++) {
        mapStrip = testMap[row];
        for (int col = 0; col < mapStrip.length(); col++) {
            //Checks to see if there is an antena at the location
            if (testMap[row][col] != '.' && IsPrevouslyChecked(row, col, previouslyCheckedFrequencies)) {
                targetChar = testMap[row][col];
                //Finds the postion of every antenna at that frequency (Doesn't check rows before since no arials garunteed)
                for (int i = row; i < testMap.size(); i++) {
                    mapStrip = testMap[i];
                    for (int j = 0; j < mapStrip.length(); j++) {
                        //Checking for the frequency to match
                        if (testMap[i][j] == targetChar && (i != row && j != col)) {
                            //If frequency matches we find the distance between the two arials and place an antinode the same distance away on each side
                            antennaDistanceX = col - j;
                            antennaDistanceY = row - i;
                            whileLoopIncrement = 0;
                            while ((i - whileLoopIncrement * antennaDistanceY) >= 0 && (i - whileLoopIncrement * antennaDistanceY) < testMap.size() && (j - whileLoopIncrement * antennaDistanceX) < mapStrip.length() &&  (j - whileLoopIncrement * antennaDistanceX) >= 0) {
                                //Place antinode on the first side
                                testMapAntinodes[(i - whileLoopIncrement * antennaDistanceY)][(j - whileLoopIncrement * antennaDistanceX)] = '#';
                                whileLoopIncrement++;

                            }
                            whileLoopIncrement = 0;
                            while ((row + whileLoopIncrement * antennaDistanceY) >= 0 && (row + whileLoopIncrement * antennaDistanceY) < testMap.size() && (col + whileLoopIncrement * antennaDistanceX) >= 0 && (col + whileLoopIncrement * antennaDistanceX) < mapStrip.length()) {
                                //Place antinode on the other side
                                testMapAntinodes[(row + whileLoopIncrement * antennaDistanceY)][(col + whileLoopIncrement * antennaDistanceX)] = '#';
                                whileLoopIncrement++;
                            }
                        }
                    }
                }


            }
        }
    }

    for (int row = 0; row < testMap.size(); row++) {
        mapStrip = testMapAntinodes[row];
        for (int col = 0; col < mapStrip.length(); col++) {
            std::cout << testMapAntinodes[row][col];
            if (testMapAntinodes[row][col] == '#') {
                value++;
            }
        }
        std::cout << "\n";
    }

    return value;
}

int main()
{
    int value = Part1();
    std::cout << value;
}


/*
Two options here:
Either we check for antenas and then look for their antinodes --- Seems easier()
-Find an antena of any frequencey
-Check for all other antenas on same frequency (we can stop at half way to the edge as then the antinode will be off the side of the map)
--Look for each at radius 1
--Look for each at radius 2
--Contunue in each direction until we reach halfway to the edges (stop since we hit the edge)
-Double the distance between the antenas and place a # at the antinode location
-Repeat for all antenas

Aleternatively, (better) we scan through the map until we reach an arial at a frequency we haven't yet identified
We then get the coordinates for every point that has an arial on the same frequency
We can iterate through comparing every set of coordiates with eachother in both directions to reach 


Or we check every position and look to see if it should be an antinode


*/