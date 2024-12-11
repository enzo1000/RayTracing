#pragma once
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Vec3.h"
#include "Ray.h"
#include "Cube.h"

#include <vector>
#include <optional>

struct Sphere {
    Vec3 center;
    float radius;
    Vec3 albedo;
};

struct Intersection {
    Vec3 point;
    Vec3 normal;
    float distance;
    Vec3 albedo;
};

//Possibilité de faire ça en C++ ? 
struct ObjectHierarchy {

    ObjectHierarchy* leftTree;
    ObjectHierarchy* rightTree;
};

// Fonction d'intersection entre un rayon et une sphère
//Englobe la fonction intersect_sphere et l'implementation Intersectable for Sphere
std::optional<Intersection> intersect_sphere(const Ray& ray, const Sphere& sphere) {
    //Vecteur origine du rayon vers le centre
    Vec3 oc = ray.origin - sphere.center;

    //Norme du vecteur direction du rayon
    float a = ray.direction.squared_length();
    //Produit scalaire entre oc et la direction du Rayon
    float b = 2.0f * dot(oc, ray.direction);
    //Norme du vecteur oc - sphere.rayon
    float c = (oc.squared_length() - (sphere.radius * sphere.radius));

    float delta = ((b * b) - (4.0f * a * c));

    if (delta >= 0.0f) {
        // calcul des deux solutions de l'équation du second degré
        float t1 = (-b - std::sqrt(delta)) / (2.0f * a);
        float t2 = (-b + std::sqrt(delta)) / (2.0f * a);
        float t = (t1 >= 0.0f) ? t1 : t2; // on prend la solution positive

        if (t >= 0.0f) {
            Vec3 intersection_point = get_intersection_point_t(ray, t);
            Vec3 normal = (intersection_point - sphere.center).normalize();
            //De base t n'était pas mult par direction.length()
            return Intersection { intersection_point, normal, t * ray.direction.length(), sphere.albedo};
        }
    }
    return std::nullopt;
}

#endif // !INTERSECTION_H
