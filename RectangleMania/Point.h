//
//  Point.h
//  RectangleMania
//
//  Created by adeeb mohammed on 10/05/20.
//  Copyright © 2020 adeeb mohammed. All rights reserved.
//

#ifndef Point_h
#define Point_h

 struct Point {
  int x;
  int y;
     // this function is used to work in std::find
    bool operator==(Point p2){
        return x == p2.x && y == p2.y;
    }
};

#endif /* Point_h */
