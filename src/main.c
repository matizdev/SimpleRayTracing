#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct {
    float x, y, z;
} Vector3;

typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

typedef struct {
    Vector3 center;
    float radius;
} Sphere;

typedef struct {
    Vector3 position;
    Vector3 color;
    float intensity;
} Light;

Vector3 vector_add(Vector3 a, Vector3 b) {
    return (Vector3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector3 vector_sub(Vector3 a, Vector3 b) {
    return (Vector3){a.x - b.x, a.y - b.y, a.z - b.z};
}

Vector3 vector_scale(Vector3 v, float s) {
    return (Vector3){v.x * s, v.y * s, v.z * s};
}

float vector_dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 vector_normalize(Vector3 v) {
    float len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return (Vector3){v.x / len, v.y / len, v.z / len};
}

int intersect_ray_sphere(Ray ray, Sphere sphere, float *t) {
    Vector3 oc = vector_sub(ray.origin, sphere.center);
    float a = vector_dot(ray.direction, ray.direction);
    float b = 2.0f * vector_dot(oc, ray.direction);
    float c = vector_dot(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return 0;
    } else {
        *t = (-b - sqrt(discriminant)) / (2.0f * a);
        return 1;
    }
}

Vector3 trace_ray(Ray ray, Sphere sphere, Light light) {
    float t;
    if (intersect_ray_sphere(ray, sphere, &t)) {
        Vector3 hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
        Vector3 normal = vector_normalize(vector_sub(hit_point, sphere.center));
        Vector3 light_dir = vector_normalize(vector_sub(light.position, hit_point));
        float diff = fmax(0.0f, vector_dot(normal, light_dir)) * light.intensity;
        return vector_scale(light.color, diff);
    }
    return (Vector3){0, 0, 0}; // Background color
}

int main() {
    FILE *image = fopen("image.ppm", "w");
    fprintf(image, "P3\n%d %d\n255\n", WIDTH, HEIGHT);

    Sphere sphere = {{0, 0, -5}, 1};
    Light light = {{5, 5, -5}, {1, 1, 1}, 1.0f};

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            float u = (2.0f * x / WIDTH - 1.0f) * (float)WIDTH / HEIGHT;
            float v = 1.0f - 2.0f * y / HEIGHT;
            Ray ray = {{0, 0, 0}, vector_normalize((Vector3){u, v, -1})};
            Vector3 color = trace_ray(ray, sphere, light);
            fprintf(image, "%d %d %d ", (int)(color.x * 255), (int)(color.y * 255), (int)(color.z * 255));
        }
    }

    fclose(image);
    return 0;
}