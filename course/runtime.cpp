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
	DATA_TYPE xi[4]; 
	xi[0] = 0.0;
	xi[1] = 2.0;
	xi[2] = 3.0;
	xi[3] = 7.0;
	Solver solver = Solver(0, 7, 4, xi);
	solver.buildSLAE(task);
	solver.solve();
	DATA_TYPE x;
	scanf("%lf", &x);
	printf("readed x = %f\n", x);
	printf("%f\n", solver.u(x));
	return 0;
}
