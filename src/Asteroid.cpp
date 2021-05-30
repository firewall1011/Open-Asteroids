#define GLFW_INCLUDE_NONE
#include "Asteroid.h"
#include <GL/glew.h> 

vec2* AsteroidVertices(int num_vertices, float radius, float distance, const vec2& centro);

Asteroid::Asteroid(int num_vertices, float radius, float noise, vec2 center, vec2 move_dir, float speed) : Object() {
    vertices = AsteroidVertices(num_vertices, radius, noise, center);
    length = num_vertices;
    this->center = center;
    this->radius = radius;
    this->move_dir = move_dir;
    this->speed = speed;
}

void Asteroid::Draw(int first) const
{
    glDrawArrays(GL_LINE_LOOP, first, length);
}

bool Asteroid::Collision(vec2 point, float obj_radius) const
{
    return (point - center).magnitude() <= obj_radius + this->radius;
}

void Asteroid::Update(float delta_time)
{
    Move((move_dir) * speed);
    Rotate(0.005f);
}

vec2* AsteroidVertices(int num_vertices, float radius, float distance, const vec2& centro) {
    vec2* vertices = new vec2[num_vertices];

    float angle = 0.0f;
    srand(time(NULL));

    float x, y;
    for (int i = 0; i < num_vertices; i++)
    {
        float _radius = radius + (rand() / (float)RAND_MAX) * distance;
        x = (cosf(angle) * _radius) + centro.x;
        y = (sinf(angle) * _radius) + centro.y;
        vertices[i].x = x;
        vertices[i].y = y;
        angle += (2 * T_PI) / (num_vertices - 1);
    }

    return vertices;
}