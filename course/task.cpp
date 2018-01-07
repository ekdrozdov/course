#include "task.h"

Task::Task() {
	boundCondFirst = 1.0;
	boundCondSecond = -1.0;
}

DATA_TYPE Task::f(DATA_TYPE x) {
	if (x > 0.0 && x < 2.0) {
		return 0.0;
	} else if (x > 2.0 && x < 3.0) {
		return 1.0;
	} else if (x > 3.0 && x < 7.0) {
		return 0.25;
	}
	return -1000.0;
}
