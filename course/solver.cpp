#include "solver.h"

Solver::Solver() {
	A = NULL;
	b = NULL;
	fe = NULL;
	a = 0;
	c = 0;
}

Solver::Solver(int start, int end, int nodesTotal, DATA_TYPE* xi) {
	A = new DATA_TYPE[nodesTotal * 3];
	b = new DATA_TYPE[nodesTotal];
	for (DATA_TYPE* pA = A, *pB = b; pB < &b[nodesTotal]; ++pA, ++pB) {
		*pA = 0.0;
		*pB = 0.0;
	}
	for (DATA_TYPE* pA = &A[nodesTotal]; pA < &A[nodesTotal * 3]; ++pA) {
		*pA = 0.0;
	}
	q = new DATA_TYPE[nodesTotal];
	for (DATA_TYPE* pQ = q; pQ < &q[nodesTotal]; ++pQ) {
		*pQ = 0.0;
	}

	fe = new FE[nodesTotal - 1];
	for (int i = 0; i < fe->total; ++i) {
		fe[i].x1 = xi[i];
		fe[i].x2 = xi[i + 1];
		fe[i].h = xi[i + 1] - xi[i];
	}	

	a = start;
	c = end;
}

Solver::~Solver() {
	if (A) {
		delete[] A;
		A = NULL;
	}

	if (b) {
		delete[] b;
		b = NULL;
	}

	if (q) {
		delete[] q;
		q = NULL;
	}

	if (fe) {
		int total = fe->total;
		for (int i = 0; i < total; ++i) {
			fe[i].~FE();
		}
		delete[] fe;
		fe = NULL;
	}
	a = 0;
	c = 0;
}


void Solver::buildSLAE(CauchyProblem* problem) {
	DATA_TYPE* pA = A + 1;
	DATA_TYPE* pB = b;

	// Assembly SLAE by finite elements.
	for (int i = 0; i < fe->total; ++i) {
		// Assembly matrix A.
		DATA_TYPE impact = 1.0 / fe[i].h;
		*pA += impact;
		pA++;
		*pA -= impact;
		pA++;
		*pA-= impact;
		pA++;
		*pA += impact;

		// Assembly vector b.
		*pB += (fe[i].h / 6.0) * 
			(2.0 * problem->f(fe[i].x1 + 0.001) + problem->f(fe[i].x2 - 0.001));
		pB++;
		*pB += (fe[i].h / 6.0) * 
			(problem->f(fe[i].x1 + 0.001) + 2.0 * problem->f(fe[i].x2 - 0.001));
	}

	// Consider a boundary conditions.
	// A[0] is a shadow element caused by three-diagonal format,
	// so first element of the first string is actually A[1].
	A[1] = 1.0;
	A[2] = 0.0;
	b[0] = problem->boundCondFirst;
	b[fe->total] += problem->boundCondSecond;
}

void Solver::solve() {
	// Modify SLAE to tridiagonal type
	// (the problem is that A[1][2] = 0).
	b[1] = b[1] - A[3] * b[0];
	q[0] = b[0];
	// Thomas algorithm.
	// Modifying coefficients.
	A[5] = A[5] / A[4];
	b[1] = b[1] / A[4];
	for (int i = 2; i < fe->total + 1; ++i) {
		int shift = 3 * i;

		A[shift + 2] = A[shift + 2] / 
			(A[shift + 1] - A[shift] * A[shift - 1]);

		b[i] = (b[i] - A[shift] * b[i - 1]) / 
			(A[shift + 1] - A[shift] * A[shift - 1]);
	}
	
	// Back substiturion.
	q[fe->total] = b[fe->total];
	for (int i = (fe->total - 1); i >= 0; --i) {
		q[i] = b[i] - A[3 * i + 2] * q[i + 1];
	}
}

DATA_TYPE Solver::basisFunc(DATA_TYPE x, int feLeftNum, int feRigthNum) {
	if (x <= fe[feLeftNum].x1) {
		return 0.0;
	} else if (x >= fe[feLeftNum].x1 && x <= fe[feLeftNum].x2) {
		return (x - fe[feLeftNum].x1) / fe[feLeftNum].h;
	} else if (x >= fe[feRigthNum].x1 && x <= fe[feRigthNum].x2) {
		return (fe[feRigthNum].x2 - x) / fe[feRigthNum].h;
	} else {
		return 0.0;
	}
}

DATA_TYPE Solver::u(DATA_TYPE x) {
	printf("x is %f\n", x);
	if (x < a || x > c) {
		return 0;
	}
	int feContainerNum = 0;
	while (! (x < fe[feContainerNum].x2)) {
		feContainerNum++;
	}
	return basisFunc(x, feContainerNum - 1, feContainerNum) * 
		q[feContainerNum] +
		basisFunc(x, feContainerNum, feContainerNum + 1) *
		q[feContainerNum + 1];
}
