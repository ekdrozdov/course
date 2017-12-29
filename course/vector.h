/**
* SDESolver.h
* Purpose: setup and solve a system of the
* differential equations by some method.
*
* @author Edward Drozdov
* @author Dmitry Efremov
* @version 1.0d 03.11.17
*/
#pragma once
#include <math.h>
#include <stdio.h>
#define DATA_TYPE double

class Vector {
public:
	Vector();
	Vector(Vector& x);

	DATA_TYPE norm();

	void operator=(const Vector& x);
	Vector operator+(const Vector& x);
	Vector operator-(const Vector& x);
	Vector operator-();
	DATA_TYPE operator*(const Vector& x);
	Vector operator*(const DATA_TYPE& x);

	void print();

	static const int dimension = 1;
	DATA_TYPE* v;
};
