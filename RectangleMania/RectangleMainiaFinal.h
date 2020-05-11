//
//  RectangleMainiaFinal.h
//  RectangleMania
//
//  Created by adeeb mohammed on 11/05/20.
//  Copyright © 2020 adeeb mohammed. All rights reserved.
//

#ifndef RectangleMainiaFinal_h
#define RectangleMainiaFinal_h

#include <vector>
#include <unordered_map>
#include <string>
#include "Point.h"

class RectangleManiaFinal {
private:
    std::string getCordString(Point cord){
        return std::to_string(cord.x) + "-" + std::to_string(cord.y);
    }
    std::unordered_map<std::string, bool> getCordsTable(std::vector<Point> cords){
        std::unordered_map<std::string, bool> cordsTable;
        for (auto cord : cords) {
            auto cordString = getCordString(cord);
            cordsTable.insert({cordString,true});
        }
        return cordsTable;
    }
    bool isInUpperRight(Point cord1, Point cord2){
        return cord2.x > cord1.x && cord2.y > cord1.y;
    }
    int rectangleCount(std::unordered_map<std::string, bool> cordsTable,
                       std::vector<Point> cords){
        int rectangleCount = 0;
        for (auto cord1 : cords) {
            for (auto cord2 : cords) {
                if(!isInUpperRight(cord1, cord2)){
                    continue;
                }
                std::string upperCordString = getCordString(Point{cord1.x,cord2.y});
                std::string rightCordString = getCordString(Point{cord2.x,cord1.y});
                if (cordsTable.find(upperCordString) != cordsTable.end() &&
                    cordsTable.find(rightCordString) != cordsTable.end()) {
                    rectangleCount++;
                }
            }
        }
        return rectangleCount;
    }
public:
    int rectangleMania(std::vector<Point> cords){
        auto cordsTable = getCordsTable(cords);
        return  rectangleCount(cordsTable, cords);
    }
};

#endif /* RectangleMainiaFinal_h */
