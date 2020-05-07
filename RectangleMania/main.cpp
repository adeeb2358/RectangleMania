//
//  main.cpp
//  RectangleMania
//
//  Created by adeeb mohammed on 03/05/20.
//  Copyright © 2020 adeeb mohammed. All rights reserved.
// time complexity of this algorithm will be o(n^2) and space complexity is also o(n^2)

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>


struct Point {
  int x;
  int y;
    bool operator==(Point p2){
        return x == p2.x && y == p2.y;
    }
};

//four cordinate points
std::string  UP    = "up";
std::string  RIGHT = "right";
std::string  DOWN  = "down";
std::string  LEFT  = "left";

std::string cordToString(Point cord){
    return std::to_string(cord.x)+"_"+std::to_string(cord.y);
}

std::string getDirection(Point cord1, Point cord2){
    if(cord1.y == cord2.y){
        if(cord2.x > cord1.x){
            return RIGHT;
        }else{
            return LEFT;
        }
    }else if(cord1.x == cord2.x){
        if(cord2.y > cord1.y){
            return UP;
        }else{
            return DOWN;
        }
    }
    return "";
}

std::unordered_map<std::string,std::unordered_map<std::string,std::vector<Point>>>
getCordsTable(std::vector<Point> cords){
    std::unordered_map<std::string,std::unordered_map<std::string,std::vector<Point>>> cordsTable;
    for(auto cord1 : cords){
        std::unordered_map<std::string, std::vector<Point>> cord1Directions({
            {UP,std::vector<Point>()},
            {RIGHT,std::vector<Point>()},
            {DOWN,std::vector<Point>()},
            {LEFT,std::vector<Point>()},
        });
        for (auto cord2: cords) {
            std::string cord2Direction = getDirection(cord1, cord2);
            cord1Directions[cord2Direction].push_back(cord2);
        }
        std::string cord1String = cordToString(cord1);
        cordsTable.insert({cord1String, cord1Directions});
    }
    return cordsTable;
}

// function for getting next direction
std::string getNextDirection(std::string direction){
    if (direction == UP) {
        return RIGHT;
    }else if(direction == RIGHT){
        return DOWN;
    }else if(direction == DOWN){
        return LEFT;
    }
    return " ";
}

// function for counting the clockwise count of the rectangle
int countClockWiseRectangle(
                            Point cord,
                            std::unordered_map<std::string, std::unordered_map<std::string, std::vector<Point>>> cordsTable,
                            std::string direction,
                            Point orgin
    ){
    std::string cordString = cordToString(cord);
    if(direction == LEFT){
        bool rectangleFound = find(cordsTable[cordString][LEFT].begin(),
                                   cordsTable[cordString][LEFT].end(),
                                   orgin) != cordsTable[cordString][LEFT].end();
        return rectangleFound? 1:0;
    }else{
        int rectanglesCount = 0;
        std::string nextDirection = getNextDirection(direction);
        for (Point nextCord : cordsTable[cordString][direction]) {
            rectanglesCount += countClockWiseRectangle(nextCord, cordsTable, nextDirection, orgin);
        }
        return rectanglesCount;
    }
}

int countRectangles(std::vector<Point> cords,
                    std::unordered_map<std::string,std::unordered_map<std::string, std::vector<Point>>> cordsTable){
    int rectangleCount = 0;
    for (Point cord : cords) {
        rectangleCount+= countClockWiseRectangle(cord, cordsTable, UP, cord);
    }
    return rectangleCount;
}

int rectangleMania(std::vector<Point> coords){
    auto cordsTable = getCordsTable(coords);
    return countRectangles(coords,cordsTable);
}


int main(int argc, const char * argv[]) {
    std::cout << "No of rectangles formed from a set of coordinates" << std::endl;
    std::vector<Point> cords = {
      {0, 0}, {0, 1}, {1, 1}, {1, 0},
      {2, 1}, {2, 0}, {3, 1}, {3, 0},
    };
    std::cout << rectangleMania(cords);
    return 0;
}
