//point.h
#ifndef _POINTH
#define _POINTH

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {};

    // overloading so we can use std::find
    friend bool operator==(const Point& p1, const Point& p2) {
        if (p1.x == p2.x && p1.y == p2.y) return true;
        else return false;
    }
};

#endif
