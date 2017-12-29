#include "task.h"

Task::Task() {
	initCondFirst.x = 0.0;
	initCondFirst.y = 0.0;

	initCondSecond.x = 10.0;
	initCondSecond.y = 15.0;
}

DATA_TYPE Task::f(DATA_TYPE x) {
	return 2.0 * x;
}