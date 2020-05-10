//
//  main.cpp
//  RectangleMania
#include <iostream>
#include <vector>
#include "RectangleMania.h"
#include "RectangleManiaOpt.h"

int main(int argc, const char * argv[]) {
    std::cout << "No of rectangles formed from a set of coordinates" << std::endl;
    std::vector<Point> cords = {
      {0, 0}, {0, 1}, {1, 1}, {1, 0},
      {2, 1}, {2, 0}, {3, 1}, {3, 0},
    };
    RectangleMania oRectangleMania;
    std::cout << oRectangleMania.rectangleMania(cords);
    std::cout << std::endl;
    RectangleManiaOpt oRectangleManiaOpt;
    std::cout << oRectangleManiaOpt.rectangleMania(cords);
    return 0;
}
