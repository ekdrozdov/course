#include "vector.h"

Vector::Vector() {
	v = new DATA_TYPE[dimension];
	for (int i = 0; i < dimension; ++i) {
		v[i] = 0.0;
	}
}

Vector::Vector(Vector& x) {
	this->v = new DATA_TYPE[dimension];
	for (int i = 0; i < dimension; ++i) {
		this->v[i] = x.v[i];
	}
}

DATA_TYPE Vector::norm() {
	DATA_TYPE sum = 0;
	for (int i = 0; i < dimension; ++i) {
		DATA_TYPE currentElement = v[i];
		sum += currentElement * currentElement;
	}
	return sqrt(sum);
}

void Vector::operator=(const Vector& x) {
	for (int i = 0; i < dimension; ++i) {
		this->v[i] = x.v[i];
	}
}

Vector Vector::operator+(const Vector& x) {
	Vector newVector;
	for (int i = 0; i < dimension; ++i) {
		newVector.v[i] = this->v[i] + x.v[i];
	}
	return newVector;
}

Vector Vector::operator-(const Vector& x) {
	Vector newVector;
	for (int i = 0; i < dimension; ++i) {
		newVector.v[i] = this->v[i] - x.v[i];
	}
	return newVector;
}

Vector Vector::operator-() {
	Vector newVector;
	for (int i = 0; i < dimension; ++i) {
		newVector.v[i] = -(this->v[i]);
	}
	return newVector;
}

DATA_TYPE Vector::operator*(const Vector& x) {
	DATA_TYPE sum = 0;
	for (int i = 0; i < dimension; ++i) {
		sum += this->v[i] * x.v[i];
	}
	return sum;
}

Vector Vector::operator*(const DATA_TYPE& x) {
	Vector newVector;
	for (int i = 0; i < dimension; ++i) {
		newVector.v[i] = this->v[i] * x;
	}
	return newVector;
}

void Vector::print() {
	for (int i = 0; i < dimension - 1; ++i) {
		printf("%.10lf ", v[i]);
	}
	printf("%.10lf", v[dimension - 1]);
}