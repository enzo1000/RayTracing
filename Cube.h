#pragma once
#ifndef CUBE_H
#define CUBE_H

#include "Vec3.h"
#include <optional>

class AABB {
public:

	enum Axis { X, Y, Z };

	Vec3 p_min;
	Vec3 p_max;

	AABB unionCube(AABB& other) {
		return AABB(p_min.minV(other.p_min), p_max.maxV(other.p_max));
	}

	Axis largest_axis(AABB &other) {
		auto axis = this->p_max - this->p_min;

		if (axis.x >= axis.y && axis.x >= axis.z) {
			return Axis::X;
		}
		else if (axis.y >= axis.z) {
			return Axis::Y;
		}
		else {
			return Axis::Z;
		}
	}
};

/*
rayIntersectAABBRange (Ray (P ox oy oz) (N dx dy dz)) (Box (P pminx pminy pminz) (P pmaxx pmaxy pmaxz))
  | tmax'' < tmin'' = Nothing
  | otherwise = Just (tmin'', tmax'')
  where
*/
std::optional<float> intersect_cube(Ray &ray, AABB &cube) {
	auto rinvx = 1.0f / ray.direction.x;
	auto rinvy = 1.0f / ray.direction.y;
	auto rinvz = 1.0f / ray.direction.z;

	// X slab
	auto tx1 = (cube.p_min.x - ray.origin.x) * rinvx;
	auto tx2 = (cube.p_max.x - ray.origin.x) * rinvx;

	auto tmin = std::min(tx1, tx2);
	auto tmax = std::max(tx1, tx2);

	// Y slab
	auto ty1 = (cube.p_min.y - ray.origin.y) * rinvy;
	auto ty2 = (cube.p_max.y - ray.origin.y) * rinvy;

	auto tminp = std::max(tmin, std::min(ty1, ty2));
	auto tmaxp = std::min(tmax,std::max(ty1, ty2));

	// Z slab
	auto tz1 = (cube.p_min.z - ray.origin.z) * rinvz;
	auto tz2 = (cube.p_max.z - ray.origin.z) * rinvz;

	auto tminpp = std::max(tminp, std::min(tz1, tz2));
	auto tmaxpp = std::min(tmaxp, std::max(tz1, tz2));

	if (tmaxpp < tminpp) {
		return std::nullopt;
	}
	else {
		return tminpp;
	}
}

#endif // !CUBE_H
