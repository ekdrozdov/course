#include "point.h"

Point::Point() {
	x = 0;
	y = 0;
}

void Point::operator=(const Point& p) {
	x = p.x;
	y = p.y;
}

Point::Point(Point& p) {
	x = p.x;
	y = p.y;
}
