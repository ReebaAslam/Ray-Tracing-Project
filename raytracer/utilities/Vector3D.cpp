//#include "stdafx.h"
#include "Vector3D.hpp"
#include "Point3D.hpp"
#include <sstream>
#include <cmath>

Vector3D::Vector3D(const Point3D &p) {
	x = p.x;
	y = p.y;
	z = p.z;
}

Vector3D::Vector3D(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}

Vector3D::Vector3D(double c): x(c), y(c), z(c) {}

Vector3D::Vector3D(): x(0.0), y(0.0), z(0.0) {}

Vector3D & Vector3D::operator=(const Point3D &rhs){
    this->y = rhs.y;
    this->z = rhs.z;
    return (*this);
}

// Arithmetic.
Vector3D Vector3D::operator-() const {
	return Vector3D(-x, -y, -z);
}


Vector3D Vector3D::operator+(const Vector3D &v) const {
	return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D & Vector3D::operator+=(const Vector3D &v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

Vector3D Vector3D::operator-(const Vector3D &v) const {
	return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D Vector3D::operator-=(const Vector3D &v) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

// Scaling.
Vector3D Vector3D::operator*(const double a) const{
	return Vector3D(x*a, y*a, z*a);
}

Vector3D Vector3D::operator/(const double a) const {
	return Vector3D(x / a, y / a, z / a);
}


void Vector3D::normalize() {
	double len = length();
	*this = *this / len;
}

// Length.
double Vector3D::length() const {
	auto sum = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
	return std::sqrt(sum);
}

double Vector3D::len_squared() const {
	return std::pow(length(), 2);
}

// Vector products.
double Vector3D::operator*(const Vector3D &b) const {
	return x*b.x + y*b.y + z*b.z;

}
Vector3D Vector3D::operator^(const Vector3D &v) const {
	double prodX = y*v.z - z*v.y;
	double prodY = z*v.x - x*v.z;
	double prodZ = x*v.y - y*v.x;
	return Vector3D(prodX, prodY, prodZ);
}

// Scaling.
Vector3D operator*(const double a, const Vector3D &v) {
	return Vector3D(a*v.x, a*v.y, a*v.z);
}


std::string Vector3D::to_string() const {
	std::ostringstream ss;
	ss <<"Vec("<< x << ", " << y << ", " << z << ")";
	return ss.str();
}