//#include <fstream>
//#include <cmath>
//#include <optional>
//#include <vector>
//#include <algorithm>
//#include <cstdint>
//
//#include "Intersection.h"
//
//struct Light {
//    Vec3 origin;
//    Vec3 emission;
//};
//
//struct Scene {
//    std::vector<Light> lights;
//    std::vector<Sphere> spheres;
//};
//
//// Calcul de l'intersection avec toutes les sphères
//std::optional<Intersection> intersect_scene(const Ray& ray, const Scene& scene) {
//    std::optional<Intersection> closest_intersection;
//
//    for (const auto& sphere : scene.spheres) {
//        auto intersection = intersect_sphere(ray, sphere);
//        if (intersection && (!closest_intersection || intersection->distance < closest_intersection->distance)) {
//            closest_intersection = intersection;
//        }
//    }
//    return closest_intersection;
//}
//
//// Calcul du tonemapping pour ajuster la couleur
//Vec3 tonemap(const Vec3& color, float scale) {
//    return { std::min(255.0f, color.x * scale), std::min(255.0f, color.y * scale), std::min(255.0f, color.z * scale) };
//}
//
//// Fonction principale pour lancer les rayons et calculer les ombrages
//Vec3 trace_ray(const Ray& ray, const Scene& scene) {
//    auto intersection = intersect_scene(ray, scene);
//    if (!intersection) {
//        return { 0.0f, 0.0f, 0.0f };  // Couleur de fond
//    }
//
//    Vec3 color = { 0.0f, 0.0f, 0.0f };
//    for (const auto& light : scene.lights) {
//        Vec3 to_light = light.origin - intersection->point;
//        float light_distance = to_light.length();
//        Vec3 light_dir = to_light.normalize();
//
//        float cos_theta = std::max(0.0f, dot(intersection->normal, light_dir));
//        Vec3 intensity = intersection->albedo * (cos_theta / light_distance) * light.emission;
//
//        color = color + intensity;
//    }
//
//    return tonemap(color, 1.0f);
//}
//
//// Fonction pour enregistrer l'image
//void save_image(const std::vector<uint8_t>& image, int width, int height, const std::string& filename) {
//    std::ofstream file(filename, std::ios::out | std::ios::binary);
//    file << "P6\n" << width << " " << height << "\n255\n";
//    file.write(reinterpret_cast<const char*>(image.data()), image.size());
//    file.close();
//}
//
//int main() {
//    int width = 800;
//    int height = 800;
//
//    std::vector<Sphere> spheres = {
//        {{0.0f, 0.0f, 200.0f}, 180.0f, {1.0f, 0.0f, 0.5f}},
//        {{-300.0f, -300.0f, 200.0f}, 180.0f, {0.0f, 0.5f, 1.5f}},
//        {{160.0f, 0.0f, 50.0f}, 50.0f, {2.0f, 2.0f, 2.0f}},
//        {{0.0f, 50700.0f + 800.0f, 0.0f}, 50000.0f, {1.0f, 1.0f, 1.0f}}
//    };
//
//    std::vector<Light> lights = {
//        {{5000.0f, 100.0f, 0.0f}, {800000.0f, 400000.0f, 400000.0f}},
//        {{0.0f, -1000.0f, 0.0f}, {100.0f, 0.0f, 100000.0f}},
//        {{-1000.0f, 1000.0f, 0.0f}, {100000.0f, 0.0f, 50000.0f}}
//    };
//
//    float focal = 1000.0f;
//    std::vector<uint8_t> image(width * height * 3);
//
//    Scene scene1 = { lights, spheres};
//
//    //create_recursive_box(4, width, height);
//
//    for (int y = 0; y < height; ++y) {
//        for (int x = 0; x < width; ++x) {
//            Vec3 pixel = { float(x) * 2.0f - width, float(y) * 2.0f - height, 0.0f };
//            Vec3 focal_point = { 0.0f, 0.0f, -focal };
//            Vec3 direction = (pixel - focal_point).normalize();
//
//            Ray ray = Ray(pixel, direction);
//            Vec3 color = trace_ray(ray, scene1);
//
//            image[(y * width + x) * 3 + 0] = static_cast<uint8_t>(color.x);
//            image[(y * width + x) * 3 + 1] = static_cast<uint8_t>(color.y);
//            image[(y * width + x) * 3 + 2] = static_cast<uint8_t>(color.z);
//        }
//    }
//
//    save_image(image, width, height, "img.ppm");
//    std::cout << "Image saved as result.ppm\n";
//    return 0;
//}
//


#include <iostream>
#include <fstream>
#include <cmath>
#include <optional>
#include <vector>
#include <algorithm>
#include <cstdint>

// Structure de Vecteur 3D
struct Vec3 {
    float x, y, z; // coordonnées du vecteur

    // Opérateurs de vecteurs
    Vec3 operator-(const Vec3& other) const {
        return { x - other.x, y - other.y, z - other.z };   // soustraction de vecteurs par un autre vecteur
    }
    Vec3 operator+(const Vec3& other) const {
        return { x + other.x, y + other.y, z + other.z };   // addition de vecteurs par un autre vecteur
    }
    Vec3 operator*(float scalar) const {
        return { x * scalar, y * scalar, z * scalar };      // multiplication de vecteurs par un float
    }
    Vec3 operator*(const Vec3& other) const {
        return { x * other.x, y * other.y, z * other.z };   // multiplication de vecteurs par un autre vecteur
    }
    Vec3 operator/(int scalar) const {
        return { x / scalar, y / scalar, z / scalar };      // multiplication de vecteurs par un int
    }
};


// Produit scalaire
float dot(const Vec3& a, const Vec3& b) {
    return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

// Calcul de la norme d'un vecteur 3D pour avoir sa longueur
float length(const Vec3& a) {
    return std::sqrt(dot(a, a));
}
// Normalisation d'un vecteur 3D
Vec3 normalize(const Vec3& v) {
    float len = length(v);
    return { v.x / len, v.y / len, v.z / len };
}

// Norme au carré
float length_squared(const Vec3& a) {
    return dot(a, a);
}

// structure de Sphère
struct Sphere {
    Vec3 center;
    float radius;
    Vec3 albedo;
};

// structure de Rayon
struct Ray {
    Vec3 origin;
    Vec3 direction;
};

struct Light {
    Vec3 origin;
    Vec3 emission;
};

struct Intersection {
    Vec3 point;
    Vec3 normal;
    float distance;
    Vec3 albedo;
};

// Fonction d'intersection entre un rayon et une sphère
std::optional<Intersection> intersect_sphere(const Ray& ray, const Sphere& sphere) {
    Vec3 oc = ray.origin - sphere.center; // vecteur entre l'origine du rayon et le centre de la sphère

    float a = length_squared(ray.direction); // norme du vecteur direction du rayon
    float b = 2.0f * dot(oc, ray.direction); // produit scalaire entre le vecteur oc et le vecteur direction du rayon
    float c = length_squared(oc) - sphere.radius * sphere.radius; // norme du vecteur oc - rayon de la sphère

    float delta = b * b - 4.0f * a * c;

    if (delta >= 0.0f) {
        // calcul des deux solutions de l'équation du second degré
        float t1 = (-b - std::sqrt(delta)) / (2.0f * a);
        float t2 = (-b + std::sqrt(delta)) / (2.0f * a);
        float t = (t1 >= 0.0f) ? t1 : t2; // on prend la solution positive

        if (t >= 0.0f) {
            Vec3 intersection_point = ray.origin + ray.direction * t;
            Vec3 normal = normalize(intersection_point - sphere.center);
            return Intersection{ intersection_point, normal, t, sphere.albedo };
        }
    }
    return std::nullopt;
}

// Calcul de l'intersection avec toutes les sphères
std::optional<Intersection> intersect_scene(const Ray& ray, const std::vector<Sphere>& spheres) {
    std::optional<Intersection> closest_intersection;
    for (const auto& sphere : spheres) {
        auto intersection = intersect_sphere(ray, sphere);
        if (intersection && (!closest_intersection || intersection->distance < closest_intersection->distance)) {
            closest_intersection = intersection;
        }
    }
    return closest_intersection;
}


// Calcul du tonemapping pour ajuster la couleur
Vec3 tonemap(const Vec3& color, float scale) {
    return { std::min(255.0f, color.x * scale), std::min(255.0f, color.y * scale), std::min(255.0f, color.z * scale) };
}

// Fonction principale pour lancer les rayons et calculer les ombrages
Vec3 trace_ray(const Ray& ray, const std::vector<Sphere>& spheres, const std::vector<Light>& lights) {
    auto intersection = intersect_scene(ray, spheres);
    if (!intersection) {
        return { 0.0f, 0.0f, 0.0f };  // Couleur de fond
    }

    Vec3 color = { 0.0f, 0.0f, 0.0f };

    //On choisit une lampe aleatoire entre 0 et lights.size() exclue
    int aleaLight = rand() % lights.size();

    //Implémentation lumière aléatoire puis multiplication par la somme des lumières
    Light light = lights[aleaLight];
    
    Vec3 to_light = light.origin - intersection->point;
    float light_distance = length(to_light);
    Vec3 light_dir = normalize(to_light);

    float cos_theta = std::max(0.0f, dot(intersection->normal, light_dir));
    Vec3 intensity = intersection->albedo * (cos_theta / light_distance) * light.emission;

    color = color + (intensity * lights.size());
  
    //Précédente fonction pour le calcul de lumières
 
    //for (const auto& light : lights) {
    //    Vec3 to_light = light.origin - intersection->point;
    //    float light_distance = length(to_light);
    //    Vec3 light_dir = normalize(to_light);

    //    float cos_theta = std::max(0.0f, dot(intersection->normal, light_dir));
    //    Vec3 intensity = intersection->albedo * (cos_theta / light_distance) * light.emission;

    //    color = color + intensity;
    //}

    return tonemap(color, 1.0f);
}

// Fonction pour enregistrer l'image
void save_image(const std::vector<uint8_t>& image, int width, int height, const std::string& filename) {
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    file << "P6\n" << width << " " << height << "\n255\n";
    file.write(reinterpret_cast<const char*>(image.data()), image.size());
    file.close();
}

int main() {
    int width = 800;
    int height = 800;
    int ResAntiAlias = 10;

    std::vector<Sphere> spheres = {
        {{0.0f, 0.0f, 200.0f}, 180.0f, {1.0f, 0.0f, 0.5f}},
        {{-300.0f, -300.0f, 200.0f}, 180.0f, {0.0f, 0.5f, 1.5f}},
        {{160.0f, 0.0f, 50.0f}, 50.0f, {2.0f, 2.0f, 2.0f}},
        {{0.0f, 50700.0f + 800.0f, 0.0f}, 50000.0f, {1.0f, 1.0f, 1.0f}}
    };
    
    std::vector<Light> lights = {
        {{5000.0f, 100.0f, 0.0f}, {800000.0f, 400000.0f, 400000.0f}},
        {{0.0f, -1000.0f, 0.0f}, {100.0f, 0.0f, 100000.0f}},
        {{-1000.0f, 1000.0f, 0.0f}, {100000.0f, 0.0f, 50000.0f}}
    };

    float focal = 1000.0f;
    std::vector<uint8_t> image(width * height * 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Vec3 focal_point = { 0.0f, 0.0f, -focal };

            Vec3 color = Vec3(0, 0, 0);

            for (int antiAlias = 0; antiAlias < ResAntiAlias; antiAlias++) {

                float randValueX = rand() % 100;
                randValueX = randValueX / 100;

                float randValueY = rand() % 100;
                randValueY = randValueY / 100;

                float valX = float(x) * 2.0f - width + randValueX;
                float valY = float(y) * 2.0f - height + randValueY;

                Vec3 pixel = { valX, valY, 0.0f };
                Vec3 direction = normalize(pixel - focal_point);

                Ray ray = { pixel, direction };
                color = color + trace_ray(ray, spheres, lights);
            }

            color = color / ResAntiAlias;

            image[(y * width + x) * 3 + 0] = static_cast<uint8_t>(color.x);
            image[(y * width + x) * 3 + 1] = static_cast<uint8_t>(color.y);
            image[(y * width + x) * 3 + 2] = static_cast<uint8_t>(color.z);
        }
    }

    save_image(image, width, height, "img.ppm");
    std::cout << "Image saved as result.ppm\n";
    return 0;
}

