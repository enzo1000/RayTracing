#pragma once
#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray
{
public:
	Vec3 origin;
	Vec3 direction;

	Ray(Vec3& v, Vec3& u) {
		origin = v;
		direction = u;
	}
};


Vec3 get_intersection_point_t(const Ray& ray, float t) {
	return (ray.origin + ray.direction * t);
}

#endif 
