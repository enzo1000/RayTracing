#pragma once
#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class Vec3
{
public:
	float x, y, z;

	Vec3() {
		x = 0;
		y = 0;
		z = 0;
	}

	Vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float length() const {
		return sqrt(squared_length());
	}

	float squared_length() const {
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	// Normalisation d'un vecteur 3D
	Vec3 normalize() {
		float len = this->length();
		return { x / len, y / len, z / len };
	}

	Vec3 minV(Vec3& other) {
		Vec3 ret = Vec3(std::min(x, other.x), std::min(y, other.y), std::min(z, other.z));
	}

	Vec3 maxV(Vec3& other) {
		Vec3 ret = Vec3(std::max(x, other.x), std::max(y, other.y), std::max(z, other.z));
	}
};

inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
	return out << v.x << ' ' << v.y << ' ' << v.z;
}

//Soustraction entre 2 vecteurs
inline Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

//Addition entre 2 vecteurs
inline Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

//Multiplication entre 2 vecteurs
inline Vec3 operator*(const Vec3& u, const Vec3& v) {
	return { u.x * v.x, u.y * v.y, u.z * v.z };
}

//Multiplication dans les deux sens avec un float
inline Vec3 operator*(float i, const Vec3& v) {
	return Vec3(i*v.x, i*v.y, i*v.z);
}
inline Vec3 operator*(const Vec3& v, float t) {
	return t * v;
}


//Division vecteur avec un float
inline Vec3 operator/(const Vec3& v, float t) {
	return (1/t) * v;
}

//Division entre 2 vecteurs
inline Vec3 operator/(const Vec3& v, const Vec3& u) {
	return Vec3(v.x / u.x, v.y / u.y, v.z / u.z);
}

//Addition entre 1 vecteur et 1 float dans les deux sens
inline Vec3 operator+(const Vec3& u, const float t) {
	return Vec3(u.x + t, u.y + t, u.z + t);
}
inline Vec3 operator+(const float t, const Vec3& u) {
	return u + t;
}

//Dot product entre 2 vecteurs
inline float dot(const Vec3& u, const Vec3& v) {
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

//Vecteur unitaire
inline Vec3 unit_vector(const Vec3& v) {
	return v / v.length();
}

#endif