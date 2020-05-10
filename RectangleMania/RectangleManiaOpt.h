//
//  RectangleManiaOpt.h
//  RectangleMania
//
//  Created by adeeb mohammed on 07/05/20.
//  Copyright © 2020 adeeb mohammed. All rights reserved.
//


#ifndef RectangleManiaOpt_h
#define RectangleManiaOpt_h

#include <vector>
#include <unordered_map>
#include "Point.h"

// time complexity for this algorithm is o(n^2) and the space complexity of the algorithm is
// o(n) here the coordinates are stored exactly two times and o(2n) and since 2 is constant and eliminate
// it and finally it is o(n)

class RectangleManiaOpt{
private:
    // the three directions which we need to look
    std::string UP    = "UP";
    std::string RIGHT = "RIGHT";
    std::string DOWN  = "DOWN";
    // function for counting the rectangle clockwise
    int getClockWiseCount(Point cord1,
                          std::string direction,
                          std::unordered_map<std::string, std::unordered_map<int, std::vector<Point>>> cordsTable,
                          int lowerLeftY){
        if (direction == DOWN ) {
            for (auto cord2 : cordsTable.at("x").at(cord1.x)) {
                int lowerRightY = cord2.y;
                if (lowerLeftY == lowerRightY) {
                    return 1;
                }
            }
            return 0;
        }else{
            int rectangleCount = 0;
            if (direction == UP) {
                for (auto cord2 : cordsTable.at("x").at(cord1.x)) {
                    bool isAbove = cord2.y > cord1.y;
                    if (isAbove) {
                        rectangleCount += getClockWiseCount(cord2, RIGHT, cordsTable, lowerLeftY);
                    }
                }
            }else if(direction == RIGHT){
                for (auto cord2 : cordsTable.at("y").at(cord1.y)) {
                    bool isRight = cord2.x > cord1.x;
                    if(isRight){
                        rectangleCount += getClockWiseCount(cord2, DOWN, cordsTable, lowerLeftY);
                    }
                }
            }
            return rectangleCount;
        }
    }
    // function for getting the count of the rectangle
    int getRectangleCount(std::vector<Point> cords,
                          std::unordered_map<std::string, std::unordered_map<int, std::vector<Point>>> cordsTable){
        int rectangleCount = 0;
        for (auto cord : cords) {
            int lowerLeftY = cord.y;
            rectangleCount += getClockWiseCount(cord, UP, cordsTable, lowerLeftY);
        }
        return rectangleCount;
    }
    
    // preparing the coordinates table
    std::unordered_map<std::string, std::unordered_map<int, std::vector<Point>>>
    getCordsTable(std::vector<Point> cords){
        std::unordered_map<std::string, std::unordered_map<int ,std::vector<Point>>> cordsTable;
        cordsTable.insert({"x",std::unordered_map<int, std::vector<Point>>()});
        cordsTable.insert({"y",std::unordered_map<int, std::vector<Point>>()});
        
        for(auto cord1 : cords){
            if(cordsTable.at("x").find(cord1.x) == cordsTable.at("x").end()){
                cordsTable.at("x").insert({cord1.x,std::vector<Point>()});
            }
            if(cordsTable.at("y").find(cord1.y) == cordsTable.at("y").end()){
                cordsTable.at("y").insert({cord1.y,std::vector<Point>()});
            }
            // here the cordinates with same x is stored
            cordsTable.at("x").at(cord1.x).push_back(cord1);
            // here the cordinates with same y is stored
            cordsTable.at("y").at(cord1.y).push_back(cord1);
        }
        return cordsTable;
    }
public:
    int rectangleMania(std::vector<Point> coords){
        auto cordsTable = getCordsTable(coords);
        return getRectangleCount(coords, cordsTable);
    }
};

#endif /* RectangleManiaOpt_h */
