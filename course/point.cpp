#include "point.h"

Point::Point() {
	tn = 0;
	y = Vector();
}

void Point::operator=(const Point& p) {
	tn = p.tn;
	y = p.y;
}

Point::Point(Point& p) {
	tn = p.tn;
	y = Vector(p.y);
}
