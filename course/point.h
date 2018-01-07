#pragma once
#define DATA_TYPE double

class Point {
public:
	Point();
	Point(Point& p);
	void operator=(const Point& p);
	DATA_TYPE x;
	DATA_TYPE y;
};
