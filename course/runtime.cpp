/**
* runtime.cpp
* Purpose: 
*
* @author Edward Drozdov
* @version 1.0d 28/12/17
*/

#include "solver.h"
#include "task.h"

int main() {
	Task* task = new Task();
	Solver solver = Solver(0, 4, 5);
	solver.buildSystem(task);
	return 0;
}